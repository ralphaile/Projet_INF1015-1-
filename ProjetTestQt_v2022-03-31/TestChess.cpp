#include "ChessBoard.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Rook.hpp"
#include <gtest/gtest.h>

TEST(ChessPieceTest, KingMoves) {
    chess_gui::ChessBoard board(true);
    King king(Piece::Color::White, &board,true);
    QPoint initial(4, 4);

    // Test valid moves
    QPoint validMove(5, 4);
    EXPECT_TRUE(king.isValidMove(initial, validMove));

    validMove = QPoint(3, 4);
    EXPECT_TRUE(king.isValidMove(initial, validMove));

    validMove = QPoint(4, 3);
    EXPECT_TRUE(king.isValidMove(initial, validMove));

    validMove = QPoint(4, 5);
    EXPECT_TRUE(king.isValidMove(initial, validMove));

    // Test invalid moves
    QPoint invalidMove(2, 4);
    EXPECT_FALSE(king.isValidMove(initial, invalidMove));

    invalidMove = QPoint(4, 2);
    EXPECT_FALSE(king.isValidMove(initial, invalidMove));
}

// Test for valid Rook moves
TEST(ChessPieceTest, RookMoves) {
    chess_gui::ChessBoard board(true);
    Rook rook(Piece::Color::White, &board);
    QPoint initial(4, 4);

    // Test valid moves
    QPoint validMove(6, 4);
    EXPECT_TRUE(rook.isValidMove(initial, validMove));

    validMove = QPoint(4, 6);
    EXPECT_TRUE(rook.isValidMove(initial, validMove));

    // Test invalid moves
    QPoint invalidMove(6, 6);
    EXPECT_FALSE(rook.isValidMove(initial, invalidMove));

    invalidMove = QPoint(2, 2);
    EXPECT_FALSE(rook.isValidMove(initial, invalidMove));
}

// Test for valid Knight moves
TEST(ChessPieceTest, KnightMoves) {
    chess_gui::ChessBoard board(true);
    Knight knight(Piece::Color::White, &board);
    QPoint initial(4, 4);

    // Test valid moves
    QPoint validMove(6, 5);
    EXPECT_TRUE(knight.isValidMove(initial, validMove));

    validMove = QPoint(6, 3);
    EXPECT_TRUE(knight.isValidMove(initial, validMove));

    validMove = QPoint(5, 6);
    EXPECT_TRUE(knight.isValidMove(initial, validMove));

    // Test invalid moves
    QPoint invalidMove(4, 6);
    EXPECT_FALSE(knight.isValidMove(initial, invalidMove));

    invalidMove = QPoint(6, 6);
    EXPECT_FALSE(knight.isValidMove(initial, invalidMove));
}

TEST(ChessBoardTest, ValidPieceMoves) {
    chess_gui::ChessBoard board(true);

    // Get the white knight piece
    QSharedPointer<Piece> whiteKnight = board.getPiece(0, 5);
    ASSERT_TRUE(whiteKnight);

    // Test a valid move for the white knight
    EXPECT_TRUE(whiteKnight->isValidMove(QPoint(0, 5), QPoint(2, 4)));

    // Test an invalid move for the white knight
    EXPECT_FALSE(whiteKnight->isValidMove(QPoint(0, 5), QPoint(2, 5)));

    // Get the black rook piece
    QSharedPointer<Piece> blackRook = board.getPiece(7, 3);
    ASSERT_TRUE(blackRook);

    // Test a valid move for the black rook
    EXPECT_TRUE(blackRook->isValidMove(QPoint(7, 3), QPoint(5, 3)));

    // Test an invalid move for the black rook
    EXPECT_FALSE(blackRook->isValidMove(QPoint(7, 3), QPoint(5, 4)));
}

/*TEST(ChessTest, TestCheck) {
    ChessBoard board;
    board.test_initializeBoard();

    // Move the piece manually using the getPiece method
    QSharedPointer<Piece> piece1 = board.getPiece(0, 3);
    board.pieces[3][3] = piece1;
    board.pieces[0][3].clear();

    QSharedPointer<Piece> piece2 = board.getPiece(3, 3);
    board.pieces[7][3] = piece2;
    board.pieces[3][3].clear();

    EXPECT_TRUE(board.test_isInCheck(Piece::Color::Black));
}*/




