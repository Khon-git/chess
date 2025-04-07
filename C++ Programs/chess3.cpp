//STL files required for the program
#include <iostream> // Necessary to actually receive input and send output
#include <map> // Necessary for mapping the pieces to unicode representations and cleaner code
#include <vector> // Used for the actual board. Though you could use an array, vectors in my opinion are easier to work with.
#include <regex> // Used in the input function
#include <limits> // Used to clear the input buffer if previous input is invalid and the program requires new input
#include <random> // May or may not be used. It's necessary for randomly assigning the colors to each player
#include <ctime> // Used to access the system time, which is used to set the random seed in conjunction with the above STL file
#include <string> // Converting ints to strings

//I forgot why I have these last 2 but I'm too scared to remove them :<
#include <cctype> 
#include <algorithm> 

//function to spam lines, taking in the number of lines as an argument
void lines(int num) {
	for(int i=0; i < num; i++) {
		std::cout << "\n";
	}

}


//map pieces to unicode representations, as well as tiles
std::map<std::string, std::string> piecesmap = {
	{"BKing", "\u2654"},
	{"BQueen", "\u2655"},
	{"BRook", "\u2656"},
	{"BBishop", "\u2657"},
	{"BKnight", "\u2658"},
	{"BPawn", "\u2659"},
	{"WKing", "\u265A"},
	{"WQueen", "\u265B"},
	{"WRook", "\u265C"},
	{"WBishop", "\u265D"},
	{"WKnight", "\u265E"},
	{"WPawn", "\u265F"},
    {"Tile", " "}
};


//piece class
class Piece{
public:
std::string color, value, piece, representation;

int moves, num;

int passant = 0;
bool canpromote = 0;

//empty constructor is necessary for map insertion
Piece(){}

//constructor takes in color, value, and num as arguments
Piece(std::string c, std::string v, int n){

    //stores color, value, and number, and uses them to derive piece and representation
    color = c;
    value = v;
    num = n;

    piece = c + " " + v;
    representation = c[0] + v + std::to_string(n);

    //if the piece is a pawn, then it can be promoted
    if(value == "Pawn"){
        canpromote = 1;
    }
}

    //promotion function
    void promote(){
        std::string v;
        if(canpromote == 1){
            
            //array of valid pieces, with a gibberish last entry because idk how iterators work LMAOOOOO
            std::string arr[] = {"Queen", "Bishop", "Knight", "Rook", "bbvty5eresxrqwpowqpdefoife"};
            std::cout << "Select a piece to promote this pawn to: " << std::endl;


            //keeps asking for input if its not a valid piece
            while (!(std::cin >> v && std::find(std::begin(arr), std::end(arr), v) != std::end(arr))) {
                std::cout << "That is not a valid piece, try again: " << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            } 

            //updates the value (ex: "Pawn" - "Queen"), piece (ex: "White Pawn"), and representation (ex: "WPawn17")
            value = v;
            piece = color + " " + value;
            representation = color[0] + value + std::to_string(num);
			canpromote = 0;
        }
    }

};


//player class, MIGHT NOT USE THIS, depends on my mood hahahahaha
class Player {
    public:
        std::string color, name;
        int number;
        Player(int num) {
            std::cout << "Name of player " << std::to_string(num) << "? ";
            std::getline(std::cin, name);
            number = num;
    }
    
};


//chessboard class
class Chessboard{
public:
	//starting board
	std::vector<std::vector<std::string>> board = {
		{"BRook3", "BKnight7", "BBishop5", "BQueen2", "BKing1", "BBishop6", "BKnight8", "BRook4"},
		{"BPawn9", "BPawn10", "BPawn11", "BPawn12", "BPawn13", "BPawn14", "BPawn15", "BPawn16"},
		{"Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile"},
		{"Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile"},
		{"Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile"},
		{"Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile"},
		{"WPawn25", "WPawn26", "WPawn27", "WPawn28", "WPawn29", "WPawn30", "WPawn31", "WPawn32"},
		{"WRook19", "WKnight23", "WBishop21", "WQueen18", "WKing17", "WBishop22", "WKnight24", "WRook20"}
	};

    //initialize the piece objects and maps them to strings on the board
	std::map<std::string, Piece> pieces;
	void makepieces() {
		//make black pieces
		pieces["BKing1"] = Piece("Black", "King", 1);
		pieces["BQueen2"] = Piece("Black", "Queen", 2);
		pieces["BRook3"] = Piece("Black", "Rook", 3);
		pieces["BRook4"] = Piece("Black", "Rook", 4);
		pieces["BBishop5"] = Piece("Black", "Bishop", 5);
		pieces["BBishop6"] = Piece("Black", "Bishop", 6);
		pieces["BKnight7"] = Piece("Black", "Knight", 7);
		pieces["BKnight8"] = Piece("Black", "Knight", 8);
		pieces["BPawn9"] = Piece("Black", "Pawn", 9);
		pieces["BPawn10"] = Piece("Black", "Pawn", 10);
		pieces["BPawn11"] = Piece("Black", "Pawn", 11);
		pieces["BPawn12"] = Piece("Black", "Pawn", 12);
		pieces["BPawn13"] = Piece("Black", "Pawn", 13);
		pieces["BPawn14"] = Piece("Black", "Pawn", 14);
		pieces["BPawn15"] = Piece("Black", "Pawn", 15);
		pieces["BPawn16"] = Piece("Black", "Pawn", 16);

		//make white pieces
		pieces["WKing17"] = Piece("White", "King", 17);
		pieces["WQueen18"] = Piece("White", "Queen", 18);
		pieces["WRook19"] = Piece("White", "Rook", 19);
		pieces["WRook20"] = Piece("White", "Rook", 20);
		pieces["WBishop21"] = Piece("White", "Bishop", 21);
		pieces["WBishop22"] = Piece("White", "Bishop", 22);
		pieces["WKnight23"] = Piece("White", "Knight", 23);
		pieces["WKnight24"] = Piece("White", "Knight", 24);
		pieces["WPawn25"] = Piece("White", "Pawn", 25);
		pieces["WPawn26"] = Piece("White", "Pawn", 26);
		pieces["WPawn27"] = Piece("White", "Pawn", 27);
		pieces["WPawn28"] = Piece("White", "Pawn", 28);
		pieces["WPawn29"] = Piece("White", "Pawn", 29);
		pieces["WPawn30"] = Piece("White", "Pawn", 30);
		pieces["WPawn31"] = Piece("White", "Pawn", 31);
		pieces["WPawn32"] = Piece("White", "Pawn", 32);
	}

    //function to display the board
    void DisplayBoard() {
		std::cout << "\u200A\u200A A  B  C  D  E  F  G  H" << std::endl;
		std::cout << "  \u200A\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\n";
		for (int i=0; i<8; i++) {
			std::cout << 8-i << "\u2006" << '|';
			for(int j=0; j<8; j++) {

				std::string tofind = board[i][j];
				std::regex tofindregex("([A-Za-z]+).*");
				std::smatch match;
				std::regex_match(tofind, match, tofindregex);

				std::cout << piecesmap[match[1]] << " " << '|';
			}
			std::cout << "  \n  \u200A\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\n";
		}
	}

	//function to assign colors to each player. ALSO MIGHT NOT USE!
	void assigncolors(Player& p1, Player& p2, std::map<std::string, std::string>& map) {
		std::vector<std::string> colors = {"Black", "White"};
		int randomindex = std::rand() % colors.size();
		p1.color = colors.at(randomindex);
		colors.erase(colors.begin()+randomindex);
		p2.color = colors.at(0);

		std::string cont;

		map[p1.color] = p1.name;
		map[p2.color] = p2.name;
		std::cout << "Player 1 (" << p1.name << ") is: " << p1.color << std::endl;
		std::cout << "Player 2 (" << p2.name << ") is: " << p2.color << std::endl;
		std::cout << "Continue";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}


	//function to check if a piece at a specified location is the specified color
	bool iscolor(std::string color, int column, int row) {
		if(pieces[board[row][column]].color == color) {
			return 1;
		}
		return 0;
	}

	//function to check if the king can actually castle, the piece has to be a king and it has to have taken 0 moves
	bool cancastle(Piece& king) {
		if(king.moves == 0 && king.value == "King") {
			return 1;
		}
		return 0;
	}


	//function to check if a location is actually on the board
	//used to avoid try-throw-catch hell!!! 
	bool onboard(int row, int column) {
		if(row > 7 || row < 0 || column > 7 || column < 0) {
			return 0;
		}
		return 1;
	}


	//function to check if a position on the board has a piece or not
	bool haspiece(int row, int column) {
		if(board.at(row).at(column) != "Tile") {
			return 1;
		}
		return 0;
	}


	//function to update the passant-status of each pawn after every turn
	void updatepassantstatus(){
		for(const auto& x : board.at(3)){
			pieces[x].passant++;
		}
	}


	//my set of input functions
	std::string input(){
		std::string in;
		std::regex re("^([A-H])([1-8])$");
		std::smatch match;

		do{
		std::cout << "Select the location of the piece to move: " << std::endl;
		std::cin >> in;
			if(!(std::regex_match(in, match, re))){
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid location, try again!";
			}
		} while(!(std::regex_match(in, match, re)));

		return in;
	}

	int extractrow(std::string input){
		char in = input[1];
		in = in - '0';
		in = int (in);
		return 8-in;


	}

	int extractcolumn(std::string input){
		char in = input[0];
		in = in - 'A';
		return in;
	}





	//check if a move is VALID, meaning that a piece could move there if not for any external influences (like the move leading to check)
	bool validmove(int crow, int ccol, int nrow, int ncol) {
		//map which contains all the valid moves
		std::map<int, bool> validmoves = {};
		int row, col;

		//variable which contains the current piece
		std::string currentpiece = pieces[board.at(crow).at(ccol)].value;

		std::string color = pieces[board.at(crow).at(ccol)].color;

		//checks moves for pawns
		if (currentpiece == "Pawn") {
			if (pieces[board.at(crow).at(ccol)].color == "White") {

				
				std::vector<std::pair<int, int>> points = {{0,-1}};

                if(pieces[board.at(crow).at(ccol)].moves == 0){
                    points.push_back({0, -2});
                }

                //regular movements (pawns can't capture forwards)
                for (const auto& point : points){
                    if(onboard(crow+point.second, ccol+point.first) == 0) {
                        continue;
                    }
                    if(haspiece(crow+point.second, ccol+point.first) == 1) {
                        continue;
                    }
                    validmoves[(crow+point.second)*8 + ccol+point.first] = 1;
                }

                //capturing movements 
                std::vector<std::pair<int, int>> capturing = {{-1,-1}, {1, -1}};
                
                for (const auto& point : capturing){
                    if(onboard(crow+point.second, ccol+point.first) == 0){
                        continue;
                    }
                    if(haspiece(crow+point.second, ccol+point.first) == 0){
                        continue;
                    }
                    validmoves[(crow+point.second)*8 + ccol+point.first] = 1;
                }


                //passant movements
                if(crow == 3){
					//left passant
                    if(onboard(crow, ccol-1) && haspiece(crow, ccol-1) && pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow).at(ccol-1)].color && pieces[board.at(crow).at(ccol-1)].passant <= 1){
						if(pieces[board.at(crow).at(ccol-1)].moves == 1){
							validmoves[(crow-1)*8 + ccol-1] = 1;
						}
					}

					//right passant
					if(onboard(crow, ccol+1) && haspiece(crow, ccol+1) && pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow).at(ccol+1)].color && pieces[board.at(crow).at(ccol+1)].passant <= 1){
						if(pieces[board.at(crow).at(ccol+1)].moves == 1){
							validmoves[(crow-1)*8 + ccol+1] = 1;
						}						
					}

                }


				} else {
                std::vector<std::pair<int, int>> points = {{0,1}};
                
                if(pieces[board.at(crow).at(ccol)].moves == 0){
                    points.push_back({0, 2});
                }

                //regular movements
                for (const auto& point : points){
                    if(onboard(crow+point.second, ccol+point.first) == 0) {
                        continue;
                    }
                    if(haspiece(crow+point.second, ccol+point.first) == 1) {
                        continue;
                    }
                    validmoves[(crow+point.second)*8 + ccol+point.first] = 1;
    
                }

                //capturing movements
                std::vector<std::pair<int, int>> capturing = {{-1, 1}, {1, 1}};
                
                for (const auto& point : capturing){
                    if(onboard(crow+point.second, ccol + point.first) == 0){
                        continue;
                    }
                    if(haspiece(crow+point.second, ccol+point.first) == 0){
                        continue;
                    }
                    validmoves[(crow+point.second)*8 + ccol+point.first] = 1;
                }

                //passant movements
                if(crow == 3){
					//left passant
                    if(onboard(crow, ccol-1) && haspiece(crow, ccol-1) && pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow).at(ccol-1)].color && pieces[board.at(crow).at(ccol-1)].passant <= 1){
						if(pieces[board.at(crow).at(ccol-1)].moves == 1){
							validmoves[(crow+1)*8 + ccol-1] = 1;
						}
					}

					//right passant
					if(onboard(crow, ccol+1) && haspiece(crow, ccol+1) && pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow).at(ccol+1)].color && pieces[board.at(crow).at(ccol+1)].passant <= 1){
						if(pieces[board.at(crow).at(ccol+1)].moves == 1){
							validmoves[(crow+1)*8 + ccol+1] = 1;
						}						
					}

                }


			}
		}

		if (currentpiece == "Rook") {
			//left check
			for(int i=1; i < 8; i++) {
				if(onboard(crow, ccol-i) == 0) {
					break;
				}

				if (haspiece(crow, ccol-i) == 1) {
					if(pieces[board.at(crow).at(ccol-i)].color != pieces[board.at(crow).at(ccol-i)].color) {
						validmoves[crow*8 + ccol-i] = 1;
						break;
					} else {
						break;
					}
				}
				validmoves[crow*8 + ccol-i] = 1;
			}

		//right check
		for(int i=1; i < 8; i++) {
				if(onboard(crow, ccol+i) == 0) {
					break;
				}

				if (haspiece(crow, ccol+i) == 1) {
					if(pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow).at(ccol+i)].color) {
						validmoves[crow*8 + ccol+i] = 1;
						break;
					} else {
						break;
					}
				}
				validmoves[crow*8 + ccol+i] = 1;
			}

		//top check
		for(int i=1; i < 8; i++) {
			for(int i=1; i < 8; i++) {
				if(onboard(crow+i, ccol) == 0) {
					break;
					}

				if (haspiece(crow+i, ccol) == 1) {
					if(pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow+i).at(ccol)].color) {
						validmoves[(crow+i)*8 + ccol] = 1;
						break;
					} else {
						break;
					}
				}
				validmoves[(crow+i)*8 + ccol] = 1;
				}
			}

			//bottom check
			for(int i=1; i < 8; i++) {
				for(int i=1; i < 8; i++) {
					if(onboard(crow-i, ccol) == 0) {
						break;
					}
					if (haspiece(crow-i, ccol) == 1) {
						if(pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow-i).at(ccol)].color) {
							validmoves[(crow-i)*8 + ccol] = 1;
							break;
						} else {
							break;
						}
					}
					validmoves[(crow-i)*8 + ccol] = 1;
				}
			}
		}


		if (currentpiece == "Bishop") {
			//topleft diagonal check
			for(int i=1; i < 8; i++) {
				if(onboard(crow+i, ccol-i) == 0) {
					break;
				}

				if (haspiece(crow+i, ccol-i) == 1) {
					if(pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow+i).at(ccol-i)].color) {
						validmoves[(crow+i)*8 + ccol-i] = 1;
						break;
					} else {
						break;
					}
				}
				validmoves[(crow+i)*8 + ccol-i] = 1;
			}

			//topright diagonal check
			for(int i=1; i < 8; i++) {
				if(onboard(crow+i, ccol+i) == 0) {
					break;
				}

				if (haspiece(crow+i, ccol+i) == 1) {
					if(pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow+i).at(ccol+i)].color) {
						validmoves[(crow+i)*8 + ccol+i] = 1;
						break;
					} else {
						break;
					}
				}
				validmoves[(crow+i)*8 + ccol+i] = 1;
			}


			//bottomleft diagonal check
			for(int i=1; i < 8; i++) {
				if(onboard(crow-i, ccol-i) == 0) {
					break;
				}

				if (haspiece(crow-i, ccol-i) == 1) {
					if(pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow-i).at(ccol-i)].color) {
						validmoves[(crow-i)*8 + ccol-i] = 1;
						break;
					} else {
						break;
					}
				}
				validmoves[(crow-i)*8 + ccol-i] = 1;
			}

			//bottomright diagonal check
			for(int i=1; i < 8; i++) {
				if(onboard(crow-i, ccol+i) == 0) {
					break;
				}

				if (haspiece(crow-i, ccol+i) == 1) {
					if(pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow-i).at(ccol+i)].color) {
						validmoves[(crow-i)*8 + ccol+i] = 1;
						break;
					} else {
						break;
					}
				}
				validmoves[(crow-i)*8 + ccol+i] = 1;
			}
		}


		if (currentpiece == "Knight") {
			//generate points
			std::vector<std::pair<int, int>> points;
			int xvals[] = {2, -2};
			int yvals[] = {1, -1};

			for(int x : xvals) {
				for(int y: yvals) {
					points.push_back({x, y});
				}
			}

			int yvals2[] = {2, -2};
			int xvals2[] = {1, -1};
			for(int x : xvals2) {
				for(int y: yvals2) {
					points.push_back({x, y});
				}
			}


			//check each point

			for(const auto& point : points) {
				if(onboard(crow+point.first, ccol+point.second) == 0) {
					continue;
				}
				if(haspiece(crow+point.first, ccol+point.second) == 1) {
					if(pieces[board.at(crow).at(ccol)].color == pieces[board.at(crow+point.first).at(ccol+point.second)].color) {
						continue;
					}
				}
				validmoves[(crow+point.first)*8 + ccol+point.second] = 1;


			}


		}


		if (currentpiece == "Queen") {
			//left check
			for(int i=1; i < 8; i++) {
				if(onboard(crow, ccol-i) == 0) {
					break;
				}

				if (haspiece(crow, ccol-i) == 1) {
					if(pieces[board.at(crow).at(ccol-i)].color != pieces[board.at(crow).at(ccol-i)].color) {
						validmoves[crow*8 + ccol-i] = 1;
						break;
					} else {
						break;
					}
				}
				validmoves[crow*8 + ccol-i] = 1;
			}

			//right check
			for(int i=1; i < 8; i++) {
				if(onboard(crow, ccol+i) == 0) {
					break;
				}

				if (haspiece(crow, ccol+i) == 1) {
					if(pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow).at(ccol+i)].color) {
						validmoves[crow*8 + ccol+i] = 1;
						break;
					} else {
						break;
					}
				}
				validmoves[crow*8 + ccol+i] = 1;
			}

			//top check
			for(int i=1; i < 8; i++) {

				for(int i=1; i < 8; i++) {
					if(onboard(crow+i, ccol) == 0) {
						break;
					}

					if (haspiece(crow+i, ccol) == 1) {
						if(pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow+i).at(ccol)].color) {
							validmoves[(crow+i)*8 + ccol] = 1;
							break;
						} else {
							break;
						}
					}
					validmoves[(crow+i)*8 + ccol] = 1;
				}


			}

			//bottom check
			for(int i=1; i < 8; i++) {
				for(int i=1; i < 8; i++) {
					if(onboard(crow-i, ccol) == 0) {
						break;
					}
					if (haspiece(crow-i, ccol) == 1) {
						if(pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow-i).at(ccol)].color) {
							validmoves[(crow-i)*8 + ccol] = 1;
							break;
						} else {
							break;
						}
					}
					validmoves[(crow-i)*8 + ccol] = 1;
				}
			}

			//topleft diagonal check
			for(int i=1; i < 8; i++) {
				if(onboard(crow+i, ccol-i) == 0) {
					break;
				}

				if (haspiece(crow+i, ccol-i) == 1) {
					if(pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow+i).at(ccol-i)].color) {
						validmoves[(crow+i)*8 + ccol-i] = 1;
						break;
					} else {
						break;
					}
				}
				validmoves[(crow+i)*8 + ccol-i] = 1;
			}

			//topright diagonal check
			for(int i=1; i < 8; i++) {
				if(onboard(crow+i, ccol+i) == 0) {
					break;
				}

				if (haspiece(crow+i, ccol+i) == 1) {
					if(pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow+i).at(ccol+i)].color) {
						validmoves[(crow+i)*8 + ccol+i] = 1;
						break;
					} else {
						break;
					}
				}
				validmoves[(crow+i)*8 + ccol+i] = 1;
			}


			//bottomleft diagonal check
			for(int i=1; i < 8; i++) {
				if(onboard(crow-i, ccol-i) == 0) {
					break;
				}

				if (haspiece(crow-i, ccol-i) == 1) {
					if(pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow-i).at(ccol-i)].color) {
						validmoves[(crow-i)*8 + ccol-i] = 1;
						break;
					} else {
						break;
					}
				}
				validmoves[(crow-i)*8 + ccol-i] = 1;
			}

			//bottomright diagonal check
			for(int i=1; i < 8; i++) {
				if(onboard(crow-i, ccol+i) == 0) {
					break;
				}

				if (haspiece(crow-i, ccol+i) == 1) {
					if(pieces[board.at(crow).at(ccol)].color != pieces[board.at(crow-i).at(ccol+i)].color) {
						validmoves[(crow-i)*8 + ccol+i] = 1;
						break;
					} else {
						break;
					}
				}
				validmoves[(crow-i)*8 + ccol+i] = 1;
			}
		}


		if (currentpiece == "King") {
			std::vector<std::pair<int, int>> points;
			int xvals[] = {-1, 0, 1};
			int yvals[] = {-1, 0, 1};
			for(int x : xvals) {
				for(int y : yvals) {
					//gotta skip (0,0), not really a valid move there 
					if(x == 0 && y == 0){
						continue;
					}
					points.push_back({x, y});
				}
			}

			for(const auto& point : points) {
				if(onboard(crow+point.first, ccol+point.second) == 0) {
					continue;
				}
				if(haspiece(crow+point.first, ccol+point.second) == 1) {
					if(pieces[board.at(crow).at(ccol)].color == pieces[board.at(crow+point.first).at(ccol+point.second)].color) {
						continue;
					}
				}
				
				validmoves[(crow+point.first)*8 + ccol+point.second] = 1;
			}
        }

		if (validmoves[nrow*8 + ncol] == 1) {
			return 1;
		}
		return 0;
	}


	//check if a move will lead to checking oneself, if it does then return 1, otherwise 0
	bool leads_to_check(int row, int newrow, int col, int newcol){
		//current color = color of current piece = color of the king
		std::string color = pieces[board.at(row).at(col)].color;


		//create a copy of the current board in order to revert the board once all the tests are done
		std::vector<std::vector<std::string>> board_save = board;

		//test it out, valid move and onboard checks will be done in the legal function

		
		board.at(newrow).at(newcol) = board.at(row).at(col); //move the piece
		board.at(row).at(col) = "Tile"; //old position becomes a tile

		//find the index of the king
		int kingrow;
		int kingcol;

		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				if(pieces[board.at(i).at(j)].value == "King" && pieces[board.at(i).at(j)].color == color){
					kingrow = i;
					kingcol = j;
					//yes I used a goto statement, sue me :)
					goto resume;
				}
			}
		}

		resume:



		//loop through all the pieces, and check if they can hit the king
		//done by checking if they have a valid move towards the king
		//pawns handled seperately

		std::string piece;
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				piece = board.at(i).at(j);

				//skip over tiles
				if(board.at(i).at(j) == "Tile"){
					continue;
				}
				
				//skip over same color pieces
				if(pieces[piece].color == color){
					continue;
				}

				//handle pawns seperately, since not all their "valid moves" can capture...
				if(pieces[piece].value == "Pawn"){
					if(validmove(row, col, kingrow, kingcol)){
						//handle colors seperately		
						if(newcol == col - 1 || newcol == col + 1){
							board = board_save;
							return 1;
						}
					}
				} else {
					if(validmove(row, col, kingrow, kingcol)){
						board = board_save;
						return 1;
					}
				}
			}
		}
		//revert the board
		board = board_save;
		return 0;
	}



	//checks if a move is LEGAL (allowed)
	//castling will be handled SEPERATELY
	bool is_legal(int row, int newrow, int col, int newcol){
		//if the desired position is not on board, then of course it's illegal
		if(onboard(newrow, newcol) == 0){
			return 0;
		}

		//invalid moves are not legal...
		if(validmove(row, col, newrow, newcol) == 0){
			return 0;
		}

		//if it leads to checking yourself, then obviously it isn't allowed
		if(leads_to_check(row, newrow, col, newcol)){
			return 0;
		}


		return 1;
	}

};







//main function

int main(){


	Piece mypiece("White", "Pawn", 1);
	mypiece.promote();
	std::cout << mypiece.value << std::endl;

}