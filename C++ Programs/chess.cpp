#include <iostream>
#include <map>
#include <vector>
#include <regex>
#include <limits>
#include <random>
#include <ctime>

//spam lines
void lines(int num){

    for(int i=0; i < num; i++){
        std::cout << "\n";
    }

}


//map pieces to unicode representations
std::map<std::string, std::string> piecesmap = {
{"BKing", "\u2654"},
{"BQueen", "\u2655"},
{"BRook", "\u2656"},
{"BRook", "\u2656"},
{"BBishop", "\u2657"},
{"BBishop", "\u2657"},
{"BKnight", "\u2658"},
{"BKnight", "\u2658"},
{"BPawn", "\u2659"},
{"WKing", "\u265A"},
{"WQueen", "\u265B"},
{"WRook", "\u265C"},
{"WBishop", "\u265D"},
{"WKnight", "\u265E"},
{"WPawn", "\u265F"},
{"WSquare", "\u25A0"},
{"BSquare", "\u25A1"}
};


class Piece{
    public:
        std::string value, color, piece;
        bool moved = 0;
        Piece(){}

        Piece(std::string c, std::string p){
            color = c;
            value = p;
            piece = color[0] + value;
        };
    
};


class Player{
    public:
    std::string color, name;
    Player(){
        std::cout << "Name of player? ";
        std::getline(std::cin, name);
    }

};


class ChessBoard{
public:
    //starting board
    std::vector<std::string> board = {
        "BRook1", "BKnight1", "BBishop1", "BQueen", "BKing", "BBishop2", "BKnight2", "BRook2",
        "BPawn1", "BPawn2", "BPawn3", "BPawn4", "BPawn5", "BPawn6", "BPawn7", "BPawn8",
        "Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile",
        "Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile",
        "Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile",
        "Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile", "Tile",
        "WPawn1", "WPawn2", "WPawn3", "WPawn4", "WPawn5", "WPawn6", "WPawn7", "WPawn8",
        "WRook1", "WKnight1", "WBishop1", "WQueen", "WKing", "WBishop2", "WKnight2", "WRook2",

    };
    
    //initialize the piece objects and maps them to strings on the board

    std::map<std::string, Piece> pieces;

    void makepieces() {
        //make black pieces
        pieces["BKing"] = Piece("Black", "King");
        pieces["BQueen"] = Piece("Black", "Queen");
        pieces["BRook1"] = Piece("Black", "Rook");
        pieces["BRook2"] = Piece("Black", "Rook");
        pieces["BBishop1"] = Piece("Black", "Bishop");
        pieces["BBishop2"] = Piece("Black", "Bishop");
        pieces["BKnight1"] = Piece("Black", "Knight");
        pieces["BKnight2"] = Piece("Black", "Knight");
        pieces["BPawn1"] = Piece("Black", "Pawn");
        pieces["BPawn2"] = Piece("Black", "Pawn");
        pieces["BPawn3"] = Piece("Black", "Pawn");
        pieces["BPawn4"] = Piece("Black", "Pawn");
        pieces["BPawn5"] = Piece("Black", "Pawn");
        pieces["BPawn6"] = Piece("Black", "Pawn");
        pieces["BPawn7"] = Piece("Black", "Pawn");
        pieces["BPawn8"] = Piece("Black", "Pawn");

        //make white pieces        
        pieces["WKing"] = Piece("White", "King");
        pieces["WQueen"] = Piece("White", "Queen");
        pieces["WRook1"] = Piece("White", "Rook");
        pieces["WRook2"] = Piece("White", "Rook");
        pieces["WBishop1"] = Piece("White", "Bishop");
        pieces["WBishop2"] = Piece("White", "Bishop");
        pieces["WKnight1"] = Piece("White", "Knight");
        pieces["WKnight2"] = Piece("White", "Knight");
        pieces["WPawn1"] = Piece("White", "Pawn");
        pieces["WPawn2"] = Piece("White", "Pawn");
        pieces["WPawn3"] = Piece("White", "Pawn");
        pieces["WPawn4"] = Piece("White", "Pawn");
        pieces["WPawn5"] = Piece("White", "Pawn");
        pieces["WPawn6"] = Piece("White", "Pawn");
        pieces["WPawn7"] = Piece("White", "Pawn");
        pieces["WPawn8"] = Piece("White", "Pawn");

    }

    void DisplayPieces(){
        for (const auto& entry: pieces){
            std::cout << entry.first << " " << piecesmap[entry.second.piece] << std::endl;
        }

    }

    void DisplayBoard(){   
    std::cout << "\u200A\u200AA B C D E F G H" << std::endl;
    for (int i=0; i<8; i++){
        std::cout << 8-i << "\u2006";
        for(int j=0; j<8; j++){
            int pos = 8*i+j;
            if (board[pos] == "Tile"){
                if (i % 2 == 0){
                    if (j % 2 == 0){
                        std::cout << piecesmap["WSquare"];
                    } else{
                        std::cout << piecesmap["BSquare"];
                    }
                } else {
                    if (j % 2 == 0){
                        std::cout << piecesmap["BSquare"];
                    } else{
                        std::cout << piecesmap["WSquare"];
                    }

                }

            }

            std::string tofind = board[pos];
            std::regex tofindregex("([A-Za-z]+).*");
            std::smatch match;
            std::regex_match(tofind, match, tofindregex);

            std::cout << piecesmap[match[1]] << " ";
        }
        std::cout << "\n";

    }
    }

    void assigncolors(Player& p1, Player& p2){
        std::vector<std::string> colors = {"Black", "White"};
        int randomindex = std::rand() % colors.size();
        p1.color = colors.at(randomindex);
        colors.erase(colors.begin()+randomindex);
        p2.color = colors.at(0);

        std::cout << "Player 1 (" << p1.name << ") is: " << p1.color << std::endl;
        std::cout << "Player 2 (" << p2.name << ") is: " << p2.color << std::endl;
    }

    int inputcolumn(){
        char column;
        std::cout << "select a column (A-H): ";
        while (!(std::cin >> column && column < 73 && column >= 65)){
            std::cout << "That is not a valid column, try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        int columnIndex = column - 'A';
        return columnIndex;
    }
    

    int inputrow(){
        int row;
        std::cout << "select a row (1-8): ";
        while(!(std::cin >> row && row < 9 && row > 0)){
            std::cout << "That is not a valid row, try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        row = 8-row;
        return row;
    }


    void displaypiece(){
        int row, column;
        row = inputrow();
        column = inputcolumn();
        std::cout << pieces[board.at((row*8) + column)].value;    

    }

    bool iscolor(std::string color){
        int row, column;
        row = inputrow();
        column = inputcolumn();
        if(pieces[board.at((row*8) + column)].color == color){
          return 1;
        }
        return 0;
    }
};



int main() {
    std::srand(time(NULL));
    

    ChessBoard chessboard;
    chessboard.makepieces();
    chessboard.DisplayBoard();

    Player p1, p2;
    chessboard.assigncolors(p1, p2);

    return 0;
}
