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
//Apparently the code works without them but they're here just in case
#include <cctype> 
#include <algorithm> 

//function to spam lines, taking in the number of lines as an argument
void lines(int num) {
	for(int i=0; i < num; i++) {
		std::cout << "\n";
	}

}


//map the pieces to unicode representations, and tiles to an appropriate amount of spaces
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

int moves = 0;
int num;

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
            
            std::string arr[] = {"Queen", "Bishop", "Knight", "Rook"};
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


//player class, not really necessary but oh well
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
	//alternatively you could simply make the board a vector of vectors of the piece objects themselves, but I didn't know how to do that when I began :P
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
		for (int i=0; i < 8; i++) {
			std::cout << 8-i << "\u2006" << '|';
			for(int j=0; j < 8; j++) {

				std::string tofind = pieces[board.at(i).at(j)].representation;

				if(board.at(i).at(j) == "Tile"){
					tofind = "Tile";
				}

				std::regex tofindregex("([A-Za-z]+).*");
				std::smatch match;
				std::regex_match(tofind, match, tofindregex);

				std::cout << piecesmap[match[1]] << " " << '|';
			}
			std::cout << "  \n  \u200A\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\n";
		}
	}

	//function to assign colors to each player
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
	bool iscolor(std::string color, int row, int column) {
		if(pieces[board[row][column]].color == color) {
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
			if(pieces[x].color == "Black"){
				pieces[x].passant++;
			}
		}
		for(const auto& x : board.at(4)){
			if(pieces[x].color == "White"){
				pieces[x].passant++;
			}
		}
	}


	//my set of input functions

	//input() uses regex to make sure the player's input matches the pattern for positions on the board (ex: A5, D3, H1)
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

	//gets the row # from the input() function
	int extractrow(std::string input){
		char in = input[1];
		in = in - '0';
		in = int (in);
		return 8-in;
	}

	//gets the column # from the input() function
	int extractcolumn(std::string input){
		char in = input[0];
		in = in - 'A';
		return in;
	}




	//check if a move is VALID, meaning that a piece could move there if not for any external influences (like the move leading to check)
	bool validmove(int crow, int ccol, int nrow, int ncol) {

		//if the position is the same as the old one, it's simply not valid
		if(crow == nrow && ccol == ncol){
			return 0;
		}


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

			//castling
			//only works if king has had 0 moves
			if(pieces[board.at(crow).at(ccol)].moves != 0){
				goto nocastle;
			}

			if(ccol != 4){
				goto nocastle;
			}

			if(in_check(color)){
				goto nocastle;
			}

			
			//FINISH CASTLE SCRIPT

			//check left
			if(pieces[board.at(crow).at(ccol - 4)].moves == 0){
				int left[3] = {-1, -2, -3};


				//first check that the rook in question has no moves
				if(pieces[board.at(crow).at(ccol-4)].value != "Rook" || pieces[board.at(crow).at(ccol-4)].moves != 0){
					goto noleft;
				}


				//next check that the spaces between the rook and king are open
				if(haspiece(crow, ccol - 1) || haspiece(crow, ccol - 2) || haspiece(crow, ccol - 3)){
					goto noleft;
				}

				//then check that they aren't being attacked
				for(const auto& point : left){
					if(is_attacked(color, crow, ccol + point)){
						goto noleft;
					}
				}
				
				validmoves[(crow*8) + (ccol-2)] = 1;
			}

			noleft:

			//check right

			if(pieces[board.at(crow).at(ccol + 3)].moves == 0){
				int right[2] = {1, 2};
				


				//first check that the rook in question has no moves
				if(pieces[board.at(crow).at(ccol+3)].value != "Rook" || pieces[board.at(crow).at(ccol+3)].moves != 0){
					goto noright;
				}


				//next check that the spaces between the rook and king are open
				if(haspiece(crow, ccol + 1) || haspiece(crow, ccol + 2)){
					goto noright;
				}


				////then check that they aren't being attacked
				for(const auto& point : right){
					if(is_attacked(color, crow, ccol + point)){
						goto noright;
					}
				}
				
				validmoves[(crow*8) + (ccol+2)] = 1;
			}
        }

		//this label is unnecessary but I added it so the code looks a bit more uniform
		noright:

        nocastle:



		if (validmoves[nrow*8 + ncol] == 1) {
			return 1;
		}
		return 0;
	}



	//check if a move will lead to checking oneself, if it does then return 1, otherwise 0
	bool leads_to_check(int row, int col, int newrow, int newcol){
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

		findking(color, kingrow, kingcol);

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
					if(validmove(i, j, kingrow, kingcol)){
						//handle colors seperately		
						if(newcol == col - 1 || newcol == col + 1){
							board = board_save;
							return 1;
						}
					}
				} else {
					if(validmove(i, j, kingrow, kingcol)){
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



	//checks if a move is legal (allowed)
	bool is_legal(int row, int col, int newrow, int newcol){
		if(col == newcol && row == newrow){
			return 0;
		}


		//if the desired position is not on board, then of course it's illegal
		if(onboard(newrow, newcol) == 0){
			return 0;
		}


		//can't take pieces of the same color
		if(pieces[board.at(row).at(col)].color == pieces[board.at(newrow).at(newcol)].color){
			return 0;
		}

		//invalid moves are not legal...
		if(validmove(row, col, newrow, newcol) == 0){
			return 0;
		}

		//if it leads to checking yourself, then obviously it isn't allowed
		if(leads_to_check(row, col, newrow, newcol)){
			return 0;
		}

		return 1;
	}


  //function to check if a piece has any valid moves
  	bool has_moves(int row, int col){
    
    //iterate through every position on the board
    for(int i = 0; i < 8; i++){
      
        for(int j = 0; j < 8; j++){
            
            if(is_legal(row, col, i, j)){
              return 1;
            }
          
        }
      
    }
    
    return 0;
  }
    
    

	void movepiece(std::string color){
    std::cout << "        " << color << " to move!\n" << std::endl;
    DisplayBoard();
	int row = 0;
    int col = 0;
    
    //seek input while user input is invalid
    do {
     	reset:
		//get the input
      	std::string inp = input();
      
      	//clear row and col, just in case
      	row = {};
      	col = {};
      
      	row = extractrow(inp);
      	col = extractcolumn(inp);
      

		if(haspiece(row, col) != true){
			std::cout << "That is not a piece!" << std::endl;
			row = {};
			col = {};
			inp = {};
	    	goto reset;
		}

      	//check if the piece is the player's color
 		if(pieces[board.at(row).at(col)].color != color){
			std::cout << "That piece is not yours!" << std::endl;
			row = {};
			col = {};
			inp = {};
	    	goto reset;
		}
      
      //check if the piece actually has a valid move
		if(has_moves(row, col) != true){
			std::cout << "That piece has no valid moves!" << std::endl;
			row = {};
			col = {};
			inp = {};
			goto reset;
		}
		
      
    } while(pieces[board.at(row).at(col)].color != color || has_moves(row, col) != true);
    
		int currentrow, newrow, currentcol, newcol;
		currentrow = row;
		currentcol = col;
		
		std::string piece = pieces[board.at(currentrow).at(currentcol)].piece;
    	//takes in an area to move until its valid
		do {
			std::cout << "Where do you want to move the " << piece << '?' << std::endl;
			std::string inp = input();
			col = extractcolumn(inp);
			row = extractrow(inp);
			newrow = row;
			newcol = col;

			if(is_legal(currentrow, currentcol, newrow, newcol) != 1){
				std::cout << "Please select a valid location!" << std::endl;
			}

    } while(is_legal(currentrow, currentcol, newrow, newcol) != 1);
    
		//moving the piece
		//handle pawns and kings seperately, they have special movements (castling and passant)
		
		std::string value = pieces[board.at(currentrow).at(currentcol)].value;
		
		if(value == "King"){
			//handling castling
			if(newrow == currentrow && (newcol != currentcol+1 || currentcol-1)){
				//moving king
				board[newrow][newcol] = board.at(currentrow).at(currentcol);
				board[currentrow][currentcol] = "Tile";
				pieces[board.at(newrow).at(newcol)].moves++;
				
				//moving rook
				if(newcol < currentcol){
					board[newrow][newcol+1] = board.at(newrow).at(0);
					board[newrow][0] = "Tile";
					pieces[board.at(newrow).at(newcol+1)].moves++;

				} else {
					board[newrow][newcol-1] = board.at(newrow).at(7);
					board[newrow][7] = "Tile";
					pieces[board.at(newrow).at(newcol-1)].moves++;
				}

			} else {
				//regular movements
				board[newrow][newcol] = board.at(currentrow).at(currentcol);
				board[currentrow][currentcol] = "Tile";
				pieces[board.at(newrow).at(newcol)].moves++;
			}
		} 
		
		if(value == "Pawn"){

			if(color == "White"){
				if(currentcol != newcol && pieces[board.at(newrow+1).at(newcol)].value == "Pawn" && pieces[board.at(newrow+1).at(newcol)].color != color){
					//passant
					board.at(newrow).at(newcol) = board.at(currentrow).at(currentcol);
					pieces[board.at(newrow).at(newcol)].moves++;
					board.at(currentrow).at(currentcol) = "Tile";
					board.at(newrow+1).at(newcol) = "Tile"; 
				} else if(currentcol != newcol && pieces[board.at(newrow).at(newcol)].color != color){
					//regular capture
					board.at(newrow).at(newcol) = board.at(currentrow).at(currentcol);
					pieces[board.at(newrow).at(newcol)].moves++;
					board.at(currentrow).at(currentcol) = "Tile";

				} else {
					//regular movement
					board.at(newrow).at(newcol) = board.at(currentrow).at(currentcol);
					pieces[board.at(newrow).at(newcol)].moves++;
					board.at(currentrow).at(currentcol) = "Tile";
					
					//promotion
					if(newrow == 0){
						pieces[board.at(newrow).at(newcol)].promote();
					}

				}

			} else {
				if(currentcol != newcol && pieces[board.at(newrow-1).at(newcol)].value == "Pawn" && pieces[board.at(newrow-1).at(newcol)].color != color){
					//passant
					board.at(newrow).at(newcol) = board.at(currentrow).at(currentcol);
					pieces[board.at(newrow).at(newcol)].moves++;
					board.at(currentrow).at(currentcol) = "Tile";
					board.at(newrow-1).at(newcol) = "Tile"; 
				} else if(currentcol != newcol && pieces[board.at(newrow).at(newcol)].color != color){
					//regular capture
					board.at(newrow).at(newcol) = board.at(currentrow).at(currentcol);
					pieces[board.at(newrow).at(newcol)].moves++;
					board.at(currentrow).at(currentcol) = "Tile";
					
				} else {
					//regular movement
					board.at(newrow).at(newcol) = board.at(currentrow).at(currentcol);
					pieces[board.at(newrow).at(newcol)].moves++;
					board.at(currentrow).at(currentcol) = "Tile";

					//promotion
					if(newrow == 7){
						pieces[board.at(newrow).at(newcol)].promote();
					}

				}
			}

		}
		
		if(value != "Pawn" && value != "King") {
			//regular pieces :)
			board[newrow][newcol] = board[currentrow][currentcol];
			pieces[board.at(newrow).at(newcol)].moves++;
			board[currentrow][currentcol] = "Tile";	
		}
				
			
	}

	//function to check if a king is in check, takes in the color of the king as an argument
	bool in_check(std::string color){
		int krow, kcol;

		//find the kings position
		findking(color, krow, kcol);


		//go through every piece and check if they can check the king
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				if(i == krow && j == kcol){
					continue;
				}

				if(haspiece(i, j) != 1){
					continue;
				}


				if(pieces[board.at(i).at(j)].color == color){
					continue;
				}


				/*
				an unconventional way to prevent infinite recursion
				is_legal() calls validmove()
				the part of validmove() that checks if the king is able to castle calls this function (kings can't castle out of check), which can result in stack overflow
				however that part of the code gets skipped if the King's "moves" variable is > 0
				so I simply incremented, then decremented it after is_legal() is called
				*/

				pieces[board.at(i).at(j)].moves++;

				if(is_legal(i, j, krow, kcol)){
					return 1;
				}
				pieces[board.at(i).at(j)].moves = pieces[board.at(i).at(j)].moves - 1;
			}
		}
		return 0;
	}


	//function to check if the tiles around the king are in check
	//returns 1 if they are
	bool around_free(std::string color){
		int yvals[] = {-1, 0, 1};
		int xvals[] = {-1, 0, 1};

		int krow;
		int kcol;
		findking(color, krow, kcol);

		for(int x : xvals){
			for(int y : yvals){
				if(x == 0 && y == 0){
					continue;
				}

				if(onboard(krow+y, kcol+x) != 1){
					continue;
				}

				if(haspiece(krow+y,kcol+x)){
					continue;
				}
				//insert a canhit function here
				if(!(is_attacked(color, krow+y, kcol+x))){
					return 1;
				}
			}

		}

		
		return 0;

	}


	//function to check if checkmate has occured
	bool ischeckmate(std::string color, std::string color2){
		int krow, kcol;
		findking(color, krow, kcol);
		
		//check if the king has any open spaces around them
		if(has_moves(krow, kcol)){
			return 0;
		}

		//check if any pieces have moves that can bring the king out of check
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				if(onboard(i, j) != 1){
					continue;
				}

				if(haspiece(i, j) != 1){
					continue;
				}

				if(iscolor(color, i, j) != 1){
					continue;
				}

				if(has_moves(i, j)){
					return 0;
				}

			}
		}

		std::cout << "CHECKMATE!" << std::endl << color2 << " wins!" << std::endl;

		return 1;

	}

	//function to check for a stalemate
	bool is_stalemate(std::string color){
		if(in_check(color)){
			return 0;
		}

		if(around_free(color) == 1){
			return 0;
		}

		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				if(haspiece(i, j) != 1){
					continue;
				}

				if(iscolor(color, i, j) != 1){
					continue;
				}

				if(has_moves(i, j)){
					return 0;
				}

			}
		}
		
		return 1;
	}
  


	//function to check if any piece of the opposing teams can capture at a given position	
	bool is_attacked(std::string color, int row, int col){
		
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				if(haspiece(i, j) != 1){
					continue;
				}

				if(pieces[board.at(i).at(j)].color == color){
					continue;
				}

				if(is_legal(i, j, row, col)){
					return 1;
				}
                
			}
		}

		return 0;

	}

	//function to find a king of a certain color
	//stores the position into two variables that get passed by reference
	void findking(std::string color, int &krow, int &kcol){
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				if(haspiece(i, j) != true){
					continue;
				}

				if(iscolor(color, i, j) && pieces[board.at(i).at(j)].value == "King"){
					krow = i;
					kcol = j;
                    break;
				}
			}
		}
	
	}
  
  
};


//STALEMATES


int main(){
	char again;

	Player p1(1);
	Player p2(2);
	std::map<std::string, std::string> colormap = {};

	restart:

	lines(2);
	//game setup
	Chessboard chessboard;
  	chessboard.makepieces();
  	chessboard.DisplayBoard();
	chessboard.assigncolors(p1, p2, colormap);
	int turn = 0;
	lines(2);

	//game loop
	while(true){

		//White's turn
		if(turn % 2 == 0){
			if(chessboard.ischeckmate("White", "Black")){
				std::cout << colormap["Black"] << " is the winner!";
				break;
			}

			chessboard.movepiece("White");

			lines(3);

			if(chessboard.in_check("Black")){
				std::cout << "    Black King is in check!" << std::endl;
			}

			if(chessboard.is_stalemate("Black")){
				std::cout << "           STALEMATE!" << std::endl;
				break;
			}

			
		}


		//Black's turn
		if(turn % 2 == 1){
			if(chessboard.ischeckmate("Black", "White")){
				std::cout << colormap["White"] << " is the winner!";
				break;
			}

			chessboard.movepiece("Black");

			lines(3);

			if(chessboard.in_check("White")){
				std::cout << "    White King is in check!" << std::endl;
			}

			if(chessboard.is_stalemate("White")){
				std::cout << "           STALEMATE!" << std::endl;
				break;
			}


		}

		turn++;

	}


	std::cout << "Would you like to play again? (Y/N): ";
	again = {};
	while (!(std::cin >> again && (std::toupper(again) != 'Y' || std::toupper(again) != 'N'))) {
		std::cout << std::endl << "Invalid response, try again: " << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	}

	if(again == 'Y'){
		goto restart;
	}

	return 0;
}
