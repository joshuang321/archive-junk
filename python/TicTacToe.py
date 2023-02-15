import random
class Player:
    def __init__(self, name, piece):
        self.name = name
        self.piece = piece

    def __str__(self):
        return "{name} {piece}".format(**self.__dict__)

    def __eq__(self, other):
        return self.name == other.name or self.piece == other.piece

    __hash__ = None
    
class TicTacToe:
    win_conditions = [[1,2,3], [4,5,6], [7,8,9],
                      [1,4,7], [2,5,8], [3,6,9],
                      [1,5,9], [3,5,9]]

    def __init__(self,*players):
        if (len(players) == 2) and isinstance(players[0], Player) and isinstance(players[1], Player):
            if players[0] != players[1]:                
                game_players = [players[0], players[1]]
                random.shuffle(game_players)
                self.turn_list = game_players * 4 + [game_players[0]]
                self.board = [None] * 9
    
    def __call__(self):
        
        def print_board(board):
            cpy_board = [index if index is not None else ' ' for index in board]
            print(cpy_board[0], cpy_board[1], cpy_board[2], '|')
            print(cpy_board[3], cpy_board[4], cpy_board[5], '|')
            print(cpy_board[6], cpy_board[7], cpy_board[8], '|')

        def win_condition(board, player, index):
            win_possible_list = TicTacToe.win_conditions[:]
            win_possible_list = [ [board[win[0] -1], board[win[1] -1], board[win[2] -1]]
                                  for win in win_possible_list
                                  if index in win]
            win_possible_list = [win for win in win_possible_list if win == [player.piece] * 3]
            if len(win_possible_list) == 0:
                return False
            else:
                return True
                
        prompt_string = "Enter index to be keyed in for {} : "
        round_winner_string = "Winner is {} "
        while(True):
            player_turn = game.turn_list.pop()
            while(True):
                try:
                    index = int(input(prompt_string.format(player_turn.name)))
                    if game.board[index - 1] is None:
                        game.board[index -1] = player_turn.piece
                        break
                    else:
                        raise IndexError
                except IndexError:
                    print("Try again")
            
            print_board(game.board)
            
            if(win_condition(game.board,player_turn, index)):
                print(round_winner_string.format(player_turn.name))
                break
