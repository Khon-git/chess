#include <iostream>
#include <map>
#include <vector>
#include <regex>
#include <limits>
#include <random>
#include <ctime>
#include <string>
#include <cctype>
#include <algorithm>


//spam lines
void lines(int num) {

	for(int i=0; i < num; i++) {
		std::cout << "\n";
	}

}


//map pieces to unicode representations
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
};


class Piece {
public:
	std::string value, color, piece, name;
	int moves = 0;
	int passant = 0;
	bool canpromote = 0;
  	bool promoted = 0;
	int num;
	Piece() {}

	Piece(std::string c, std::string p, int number) {
		color = c;
		value = p;
		name = c + " " + p;
		num = number;
    	std::string tpiece = color[0] + value;
		piece = color[0] + value + std::to_string(num);
	};

    
	std::string promote(){
		std::string thepiece; 
		if(canpromote == 1 && promoted == 0){
		  
		  std::string arr[] = {"Queen", "Bishop", "Knight", "Rook", "bbvty5eresxrqwpowqpdefoife"};
		  std::cout << "Select a piece to promote this pawn to: " << std::endl;
		
		  
		while (!(std::cin >> thepiece && std::find(std::begin(arr), std::end(arr), thepiece) != std::end(arr))) {
			std::cout << "That is not a valid piece, try again: " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		  } 
			
		value = thepiece;
		piece = color[0] + value + std::to_string(num);
		canpromote = 0;
		promoted = 1;
		
		}
		return thepiece;
	}
	  
  }; 
    



class Player {
public:
	std::string color, name;
	Player() {
		std::cout << "Name of player? ";
		std::getline(std::cin, name);
	}

};


class ChessBoard {
public:
	//starting board
	//{"BRook3", "BKnight7", "BBishop5", "BQueen2", "BKing1", "BBishop6", "BKnight8", "BRook4"}
	//{"BPawn9", "BPawn10", "BPawn11", "BPawn12", "BPawn13", "BPawn14", "BPawn15", "BPawn16"}
	std::vector<std::vector<std::string>> board = {
		{"WPawn26", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile"},
		{"BPawn9", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile"},
		{"Tile", "BPawn10", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile"},
		{"Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile"},
		{"Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile"},
		{"Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "WKing17", "Tile"},
		{"WPawn25", "Tile", "WPawn27", "WPawn28", "WPawn29", "WPawn30", "WPawn31", "WPawn32"},
		{"WRook19", "WKnight23", "WBishop21", "WQueen18", "Tile", "WBishop22", "WKnight24", "WRook20"}
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

	void DisplayBoard() {
		std::cout << "\u200A\u200A A  B  C  D  E  F  G  H" << std::endl;
		std::cout << "  \u200A\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\n";
		for (int i=0; i<8; i++) {
			std::cout << 8-i << "\u2006" << '|';
			for(int j=0; j<8; j++) {
				if (board[i][j] == "Tile") {
					std::cout << "  " << '|';
					continue;
				}

				std::string tofind = board[i][j];
				std::regex tofindregex("([A-Za-z]+).*");
				std::smatch match;
				std::regex_match(tofind, match, tofindregex);

				std::cout << piecesmap[match[1]] << " " << '|';
			}
			std::cout << "  \n  \u200A\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\u2015\n";


		}



	}

	void assigncolors(Player& p1, Player& p2) {
		std::vector<std::string> colors = {"Black", "White"};
		int randomindex = std::rand() % colors.size();
		p1.color = colors.at(randomindex);
		colors.erase(colors.begin()+randomindex);
		p2.color = colors.at(0);

		std::cout << "Player 1 (" << p1.name << ") is: " << p1.color << std::endl;
		std::cout << "Player 2 (" << p2.name << ") is: " << p2.color << std::endl;
	}

	int inputcolumn() {
		char column;
		std::cout << "select a column (A-H): ";
		while (!(std::cin >> column && column < 73 && column >= 65)) {
			std::cout << "That is not a valid column, try again: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}
		int columnIndex = column - 'A';
		return columnIndex;
	}


	int inputrow() {
		int row;
		std::cout << "select a row (1-8): ";
		while(!(std::cin >> row && row < 9 && row > 0)) {
			std::cout << "That is not a valid row, try again: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}
		row = 8-row;
		return row;
	}

	bool iscolor(std::string color, int column, int row) {
		if(pieces[board[row][column]].color == color) {
			return 1;
		}
		return 0;
	}

	bool cancastle(Piece& piece) {
		if(piece.moves == 0 && piece.value == "King") {
			return 1;
		}
		return 0;
	}


	bool haspiece(int row, int column) {
		if(board.at(row).at(column) != "Tile") {
			return 1;
		}
		return 0;
	}

	bool onboard(int row, int column) {
		if(row > 7 || row < 0 || column > 7 || column < 0) {
			return 0;
		}
		return 1;
	}

	bool validmove(int crow, int ccol, int nrow, int ncol) {

		std::map<int, bool> validmoves = {};
		int row, col;
		std::string currentpiece = pieces[board.at(crow).at(ccol)].value;

		std::string color = pieces[board.at(crow).at(ccol)].color;


		if (currentpiece == "Pawn") {
			if (pieces[board.at(crow).at(ccol)].color == "White") {
				std::vector<std::pair<int, int>> points = {{0,-1}};

                if(pieces[board.at(crow).at(ccol)].moves == 0){
                    points.push_back({0, -2});
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

	void updatepassantstatus(){
		for(const auto& x : board.at(3)){
			pieces[x].passant++;
		}
	}


	bool istrapped(int row, int col, std::string color){
		std::string piece = pieces[board.at(row).at(col)].value;
		std::vector<std::pair<int, int>> points;


		if(piece == "King"){
			int xvals[] = {-1, 0, 1};
			int yvals[] = {-1, 0, 1};

			for(const int x : xvals){
				for(const int y : yvals){
					points.push_back({x, y});
				}
			}
		}
		
		if(piece == "Queen"){
			
			int xvals[] = {-1, 0, 1};
			int yvals[] = {-1, 0, 1};

			for(const int x : xvals){
				for(const int y : yvals){
					points.push_back({x, y});
				}
			}
		
			
		}

		if(piece == "Bishop"){
			int xvals[] = {-1, 1};
			int yvals[] = {-1, 1};

			for(const int x : xvals){
				for(const int y : yvals){
					points.push_back({x, y});
				}
			}

			
		}

		if(piece == "Knight"){

			int xvals[] = {2, -2};
			int yvals[] = {1, -1};

			for(int x : xvals) {
				for(int y: yvals) {
					points.push_back({x, y});
				}
			}

			for(int y : yvals) {
				for(int x: xvals) {
					points.push_back({y, x});
				}
			}
		}

		if(piece == "Rook"){
			points = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
		}

		if(piece == "Pawn"){
			if(pieces[board.at(row).at(col)].color == "White"){
				if(pieces[board.at(row).at(col)].moves == 0){
					points.push_back({-2, 0});
				}
				points.push_back({-1, 0});

				if(onboard(row-1, col-1)){
					if(pieces[board.at(row).at(col)].color != pieces[board.at(row-1).at(col-1)].color){
						return false;
				
					}
				}
				if(onboard(row-1, col+1)){
					if(pieces[board.at(row).at(col)].color != pieces[board.at(row-1).at(col+1)].color){
						return false;
				
					}
				}

			} else {
				if(pieces[board.at(row).at(col)].moves == 0){
					points.push_back({2, 0});
				}
				points.push_back({1, 0});

				
				if(onboard(row+1, col-1)){
					if(pieces[board.at(row).at(col)].color != pieces[board.at(row+1).at(col-1)].color){
						return false;
				
					}
				}
				if(onboard(row+1, col+1)){
					if(pieces[board.at(row).at(col)].color != pieces[board.at(row+1).at(col+1)].color){
						return false;
				
					}
				}


			}
		}


		//checks if there are any valid moves

		for(auto point : points){
			if(onboard(row+point.second, col+point.first) == false){
				continue;
			}
			if(haspiece(row+point.second, col+point.first)){
				if(pieces[board.at(row).at(col)].color != pieces[board.at(row+point.second).at(col+point.first)].color){
					return false;
				}
			}
			if(board.at(row+point.second).at(col+point.first) == "Tile"){
				return false;
			}
		}

		//if no valid moves, piece is trapped, and can't move 
		return true;
	}

	bool canhit(int prow, int pcol){
		//iterate through each individual piece, check the spots they can hit
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				//skip over tiles
				if(board.at(i).at(j) == "Tile"){
					continue;
				}

				std::string piece = pieces[board.at(i).at(j)].value;
				std::string color = pieces[board.at(i).at(j)].color;

				//this applies to all other pieces besides pawns

				if(piece != "Pawn"){
					if(validmove(i,j, prow, pcol) == true){
						return true;
					}
				} else { 
					//seperate handling for pawns, they can only capture diagonally
					
					//seperate handling for colors 
					if (color == "White"){
						std::vector<std::pair<int, int>> capturing = {{-1,-1}, {-1, 1}};
						for(const auto& pair:capturing){
							if(onboard(i+pair.first, j+pair.second) == false){
								continue;
							}
							if(prow == i+pair.first && pcol == j+pair.second){
								if(pieces[board.at(prow).at(pcol)].color != pieces[board.at(i).at(j)].color){
									return true;
								}
							}
						}
					} else {
						std::vector<std::pair<int, int>> capturing = {{1,-1}, {1, 1}};
						for(const auto& pair:capturing){
							if(onboard(i+pair.first, j+pair.second) == false){
								continue;
							}

							if(prow == i+pair.first && pcol == j+pair.second){
								if(pieces[board.at(prow).at(pcol)].color != pieces[board.at(i).at(j)].color){
									return true;
								}
							}
						}
					}

				}
			
			}
		}
		return 0;
	}

	bool incheck(std::string color){
		std::string c;
		c += std::toupper(color[0]);
		c += "King";

		int row, col;

		//find king's index
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++ ){

				std::string tofind = board[i][j];
				std::regex tofindregex("([A-Za-z]+).*");
				std::smatch match;
				std::regex_match(tofind, match, tofindregex);

				if(match[1] == c){
					row = i;
					col = j;
					goto end;
				}
	
			}
		}
		end:

		if(canhit(row, col)){
			std::cout << color << " KING IS IN CHECK" << std::endl;
			return 1;
		}

		
		std::cout << color << " KING IS NOT IN CHECK" << std::endl;
		return 0;		
	}

	bool ismate(std::string color){
		std::string c;
		c += std::toupper(color[0]);
		c += "King";

		int row, col;

		//find king's index
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++ ){

				std::string tofind = board[i][j];
				std::regex tofindregex("([A-Za-z]+).*");
				std::smatch match;
				std::regex_match(tofind, match, tofindregex);

				if(match[1] == c){
					row = i;
					col = j;
					goto end;
				}
	
			}
		}
		end:

		if(incheck(color) && istrapped(row, col, color)){
			std::cout << "CHECKMATE BITCH!!!" << std::endl;
			return 1;
		}
		return 0;
	}

	void movepiece(std::string color) {
		int row = 0, column = 0;

		do {
			std::cout << "Select a piece to move: " << std::endl;
			column = inputcolumn();
			row = inputrow();

			if(iscolor(color, column, row) != true){
				std::cout << "Select a valid piece!" << std::endl;
				row = {};
				column = {};
			}

			if(istrapped(row, column, color) == true){
				std::cout << "You cannot move that piece." << std::endl;
				row = {};
				column = {};
			}
		} while(iscolor(color, column, row) != true && istrapped(row, column, color) == true);

		int currentrow, newrow, currentcol, newcol;
		currentrow = row;
		currentcol = column;
		
		do {
			std::cout << pieces[board.at(currentrow).at(currentcol)].name << std::endl;
			std::cout << "Where do you want to move the " << pieces[board.at(currentrow).at(currentcol)].name << '?' << std::endl;
			column = inputcolumn();
			row = inputrow();
			newrow = row;
			newcol = column;

			if(validmove(currentrow, currentcol, newrow, newcol) != 1){
				std::cout << "Please select a valid location!" << std::endl;
			}
		} while(validmove(currentrow, currentcol, newrow, newcol) != 1);
				
			board[newrow][newcol] = pieces[board.at(currentrow).at(currentcol)].piece;
			pieces[board.at(currentrow).at(currentcol)].moves++;
			board[currentrow][currentcol] = "Tile";

			
			if(pieces[board.at(newrow).at(newcol)].value == "Pawn"){
				if(color == "White"){
					if(pieces[board.at(newrow+1).at(newcol)].value == "Pawn" && pieces[board.at(newrow+1).at(newcol)].color != color){
						board[newrow+1][newcol] = "Tile";
					}
				}
				if(color == "Black"){
					if(pieces[board.at(newrow-1).at(newcol)].value == "Pawn" && pieces[board.at(newrow-1).at(newcol)].color != color){
						board[newrow-1][newcol] = "Tile";
					}
				}					
    	}
	}
  
  
  void canpromote(){
    //seperate handling for black and white pawns
    
    //white
    for(int i = 0; i < 8; i++){
      if(pieces[board.at(0).at(i)].value == "Pawn"){
        char letter = 65+i;
        std::cout << "Pawn: " << letter << std::to_string(i) << " can be promoted!" << std::endl;
        pieces[board.at(0).at(i)].canpromote = 1;
      }
    }
    
    
    //black
    for(int i = 0; i < 8; i++){
      if(pieces[board.at(7).at(i)].value == "Pawn"){
        char letter = 65+i;
        std::cout << "Pawn: " << letter << std::to_string(i) << "can be promoted!" << std::endl;
        pieces[board.at(0).at(i)].canpromote = 1;
      }
    }
  }

  void promo(std::string col){
	if(col == "White"){
		for(int i = 0; i < 8; i++){
			if(pieces[board.at(0).at(i)].canpromote == true){
				std::string newpiece = pieces[board.at(0).at(i)].promote();
				board.at(0).at(i) = pieces[board.at(0).at(i)].piece;
				pieces[board.at(0).at(i)].value = newpiece;
				pieces[board.at(0).at(i)].color = col;
				pieces[board.at(0).at(i)].name = pieces[board.at(0).at(i)].color + " " + pieces[board.at(0).at(i)].value;
			}
		}
	}else{
		for(int i = 0; i < 8; i++){
			if(pieces[board.at(7).at(i)].canpromote == true){
				std::string newpiece = pieces[board.at(7).at(i)].promote();
				board.at(7).at(i) = pieces[board.at(7).at(i)].piece;
				pieces[board.at(7).at(i)].value = newpiece;
				pieces[board.at(7).at(i)].color = col;
				pieces[board.at(7).at(i)].name = pieces[board.at(7).at(i)].color + " " + pieces[board.at(7).at(i)].value;
			}
		}
	}

}  
  
};


int main() {
	//random seed
	std::srand(time(NULL));
	ChessBoard chessboard;
	chessboard.makepieces();
	chessboard.DisplayBoard();
	chessboard.ismate("White");

	chessboard.canpromote();
	chessboard.promo("White");
	chessboard.DisplayBoard();
	chessboard.movepiece("White");
  
}