#include "ChessBoard.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Rook.hpp"
#include <gtest/gtest.h>
#include "CustomExceptions.hpp"

TEST(ChessBoardTest, NoMoreThanTwoKings) {
    chess_gui::ChessBoard board(true);

    // Add the first king
    EXPECT_NO_THROW(board.createPieceAtPosition<chess_model::King>(0, 0, chess_model::Piece::Color::White));

    // Add the second king
    EXPECT_NO_THROW(board.createPieceAtPosition<chess_model::King>(0, 1, chess_model::Piece::Color::Black));

    // Attempt to add a third king
    EXPECT_THROW(chess_model::King king(chess_model::Piece::Color::White, &board), TooManyKingsException);

    chess_model::King::resetCounter();
}

// Test for valid King moves
TEST(ChessPieceTest, KingMoves) {
    chess_gui::ChessBoard board(true);
    chess_model::King king(chess_model::Piece::Color::White, &board);
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

    chess_model::King::resetCounter();
}

// Test for valid Rook moves
TEST(ChessPieceTest, RookMoves) {
    chess_gui::ChessBoard board(true);
    chess_model::Rook rook(chess_model::Piece::Color::White, &board);
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
    chess_model::Knight knight(chess_model::Piece::Color::White, &board);
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

TEST(ChessBoardTest, IsInCheck) {
    chess_gui::ChessBoard board(true);

    // Set up a test board where the black king is in check
    board.createPieceAtPosition<chess_model::Rook>(3, 0, chess_model::Piece::White);
    board.createPieceAtPosition<chess_model::King>(3, 7, chess_model::Piece::Black);

    EXPECT_TRUE(board.test_isInCheck(chess_model::Piece::Color::Black));
    chess_model::King::resetCounter();
}

TEST(ChessBoardTest, MovePutsKingInCheck) {
    chess_gui::ChessBoard board(true);

    // Set up a test board where the white king is not in check
    board.createPieceAtPosition<chess_model::King>(4, 0, chess_model::Piece::White);
    board.createPieceAtPosition<chess_model::Rook>(3, 6, chess_model::Piece::Black);

    // Test if moving the white king puts it in check
    EXPECT_TRUE(board.test_isMovePuttingKingInCheck(QPoint(4, 0), QPoint(3, 0)));

    // Test if moving the black rook puts the white king in check
    EXPECT_FALSE(board.test_isMovePuttingKingInCheck(QPoint(3, 6), QPoint(4, 6)));

    chess_model::King::resetCounter();
}

TEST(ChessBoardTest, Not_Checkmate) {
    chess_gui::ChessBoard board(true);

    // Set up a test board where the black king is in check
    board.createPieceAtPosition<chess_model::Rook>(3, 0, chess_model::Piece::White);
    board.createPieceAtPosition<chess_model::King>(3, 7, chess_model::Piece::Black);

    EXPECT_FALSE(board.test_isInCheckmate(chess_model::Piece::Color::Black));
    chess_model::King::resetCounter();
}

//Decomment this section to test checkmate, but it takes a long time if checkmate is true

/*TEST(ChessBoardTest, Checkmate) {
    chess_gui::ChessBoard board(true);

    // Set up a test board where the black king is in checkmate
    board.createPieceAtPosition<chess_model::Rook>(0, 0, chess_model::Piece::White);
    board.createPieceAtPosition<chess_model::Rook>(0, 1, chess_model::Piece::White);
    board.createPieceAtPosition<chess_model::King>(7, 0, chess_model::Piece::Black);

    EXPECT_TRUE(board.test_isInCheckmate(chess_model::Piece::Color::Black));

    chess_model::King::resetCounter();
}*/