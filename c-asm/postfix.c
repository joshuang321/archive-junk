#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

const char *operands = "-+*/^()";

#define DECLARE_STACK_TYPE( type )                         \
typedef struct{                                            \
    type *buffer;                                          \
    int front;                                             \  
    int back;                                              \
} type##_stack;                                            \
                                                           \
type##_stack allocate_##type##_stack(const size_t stacksz) \
{                                                          \
    type##_stack stack;                                    \
    stack.buffer = malloc( sizeof( type ) * stacksz );     \
    stack.back = stack.front = -1;                         \
                                                           \
    return stack;                                          \
}                                                          \
                                                           \
void type##_stack_push(type##_stack *stack,const type val) \
{                                                          \
    stack->back++;                                         \
    stack->buffer[stack->back] = val;                      \
}                                                          \
                                                           \
type * type##_stack_pop(type##_stack *stack)               \
{                                                          \
    type *val = &( stack->buffer[stack->back] );           \
    stack->back--;                                         \
                                                           \
    return val;                                            \
}                                                          \
                                                           \
bool type##_stack_empty(type##_stack *stack)               \
{                                                          \
    if ( stack->back == stack->front )                     \
    {                                                      \
        return true;                                       \
    }                                                      \
    return false;                                          \
}                                                          \
                                                           \
void deallocate_##type##_stack(type##_stack * stack)       \
{                                                          \
    free( stack->buffer );                                 \
    stack->buffer = NULL;                                  \
}                                                          \
                                                           \
type type##_stack_inspect(type##_stack *stack)             \
{                                                          \
    return stack->buffer[stack->back];                     \
}

DECLARE_STACK_TYPE( double );
DECLARE_STACK_TYPE( char );

int precedence(const char operand)
{
    switch ( operand )
    {
        case '+':
            return 1;
        case '-':
            return 1;
        case '/':
            return 2;
        case '*':
            return 2;
        case '^':
            return 3;
        case '(':
            return 4;
        case ')':
            return 4;
    }
}

char* infix_to_postfix(const char *infixStr)
{
    const size_t infixStrsz = strlen( infixStr );

    char *postfixStr = malloc( infixStrsz * 2 + 2 );
    memset( postfixStr, 1, infixStrsz * 2 + 2 );
    postfixStr[0] = 0;

    char_stack temp_operands = allocate_char_stack( infixStrsz );

    char *cpyStr = infixStr;
    char *find_operands = strpbrk( infixStr, operands );
    while ( find_operands != NULL )
    {
        if ( find_operands != cpyStr )
        {
            strncat( postfixStr,  cpyStr, find_operands - cpyStr );
            strncat( postfixStr, " ", 1 );
        }
        
        while(true)
        {
            if ( !char_stack_empty( &temp_operands ) )
            {
                if ( find_operands[0] == temp_operands.buffer[temp_operands.back] && 
                    find_operands[0] == '^' )
                {
                    char_stack_push( &temp_operands,
                        find_operands[0] );
                    break;
                }
                else if ( temp_operands.buffer[temp_operands.back] == '(' )
                {
                    char_stack_push( &temp_operands,
                        find_operands[0] );
                    break;
                }
                else if ( find_operands[0] == ')' )
                {
                    while( temp_operands.buffer[temp_operands.back] != '(' )
                    {
                        strncat( postfixStr,
                            char_stack_pop( &temp_operands ), 1 );
                        strncat( postfixStr, " ", 1);
                    }

                    char_stack_pop( &temp_operands );
                    break;
                }
                else if ( precedence( find_operands[0] ) <= precedence( temp_operands.buffer[temp_operands.back] ) )
                {
                        strncat( postfixStr,
                            char_stack_pop( &temp_operands ), 1 );
                        strncat( postfixStr, " ", 1);
                }
                else
                {
                    char_stack_push( &temp_operands,
                        find_operands[0] );
                    break;
                }
            }
            else
            {
                char_stack_push( &temp_operands,
                    find_operands[0] );
                break;
            }
        }

        if ( strlen( find_operands ) > 1 )
        {
            find_operands++;
            cpyStr = find_operands;
            find_operands = strpbrk( find_operands, operands );
        }
        else
        {
            break;
        }
    }

    if ( find_operands == NULL && strlen( cpyStr ) >  0 )
    {
        strncat( postfixStr, cpyStr, strlen( cpyStr ) );
        strncat( postfixStr, " ", 1);
    }

    while ( !char_stack_empty( &temp_operands ) )
    {
        if ( temp_operands.buffer[temp_operands.back] == ')'  || 
            temp_operands.buffer[temp_operands.back] == '(' )
        {
            char_stack_pop( &temp_operands );
            continue;
        }
        else
        {
            strncat( postfixStr, char_stack_pop( &temp_operands ),
                1 );
            strncat( postfixStr, " ", 1 );
        }
    }
    postfixStr = realloc( postfixStr, strlen(postfixStr) + 1 );
    deallocate_char_stack( &temp_operands );
    free( infixStr );

    return postfixStr;
}

double evaluate_postfix(const char *postfixStr)
{
    double tempval = 0.0f;
    double_stack temp_doubles = allocate_double_stack(strlen(postfixStr) );

    char *cpyStr  = postfixStr;
    char *buf = malloc( strlen( postfixStr ) + 1 );
    memset( buf, 1, strlen( postfixStr ) + 1 );
    char *find_delims = strpbrk( postfixStr, " " );

    while ( find_delims != NULL )
    {
        strncpy( buf, cpyStr, find_delims - cpyStr );
        switch ( buf[0] )
        {
            case '*':
            tempval = double_stack_pop( &temp_doubles )[0];
            tempval = double_stack_pop( &temp_doubles )[0] *
                tempval;
            double_stack_push( &temp_doubles, tempval );
            break;

            case '/':
            tempval = double_stack_pop( &temp_doubles )[0];
            tempval = double_stack_pop( &temp_doubles )[0] /
                tempval;
            double_stack_push( &temp_doubles, tempval );
            break;

            case '-':
            tempval = double_stack_pop( &temp_doubles )[0];
            tempval = double_stack_pop( &temp_doubles )[0] -
                tempval;
            double_stack_push( &temp_doubles, tempval );
            break;

            case '+':
            tempval = double_stack_pop( &temp_doubles )[0];
            tempval = double_stack_pop( &temp_doubles )[0]  +
                tempval;
            double_stack_push( &temp_doubles, tempval );
            break;

            case '^':
            tempval = double_stack_pop( &temp_doubles )[0];
            tempval = powf( double_stack_pop( &temp_doubles )[0] , tempval );
            double_stack_push( &temp_doubles, tempval );
            break;

            default:
            tempval = atof( buf );
            memset( buf, 1, find_delims - cpyStr );
            double_stack_push( &temp_doubles, tempval );
            break;
        }

        cpyStr = find_delims + 1;
        find_delims = strpbrk( find_delims + 1, " " );
    }

    tempval = double_stack_pop( &temp_doubles )[0];
    deallocate_double_stack( &temp_doubles );
    free( buf );
    free( postfixStr );

    return tempval;
}

char* remove_whitespace(char* unmodinfix )
{
    char *modinfix = malloc( strlen( unmodinfix ) + 1 );
    strncpy( modinfix, unmodinfix, strlen( unmodinfix ) + 1 );
    char *find_whitespace = strpbrk( modinfix, " " );
    
    while( find_whitespace != NULL )
    {
        memmove( find_whitespace, find_whitespace + 1,
            strlen( find_whitespace + 1 ) + 1);
        if ( (int) (find_whitespace + 1 )[0] == 0 )
        {
            break;
        }
        find_whitespace = strpbrk( find_whitespace + 1, " " );
    }
    return modinfix;
}

double  evaluate_string( const char *string )
{
    char* tempStr = remove_whitespace( string );
    tempStr = infix_to_postfix( tempStr );
    return evaluate_postfix( tempStr );
}

int main(int argc, const char* argv[])
{

    if ( argc == 2 )
    {
        //double val = evaluate_string( argv[1] );
        char *tempStr = remove_whitespace( argv[1] );
        tempStr = infix_to_postfix( tempStr );

        //printf( "Value: %lf \n", val );
        printf( "{%s}", tempStr );
        free( tempStr );
    }

    return 0;
}