using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AI
{

    int[] Move(int[] testBoard, int move)
    {
        int counter = testBoard[move];
        for (int drops = 0; drops<=counter; drops++){
            if (move + drops == 6)
            {
                move++;
            }
            if (move + drops < 14)
                testBoard[move + drops]++;
            else
                testBoard[move + drops - 14]++;
        }
        return testBoard;
    }

    int assess(int[] board, int move)
    {
        int value = 0;
        int resulthole = (board[move] + move) % 14;
        if (move + board[move] > 13 || resulthole <= move)
        {
            resulthole++;
            value++;
        }
        if (resulthole == 13)
        {
            value++;
            int[] testBoard = Move(board, move);
            List<int> nextMoves = legalMoveFinder(testBoard);
            Vector3 bestMove = new Vector3(7, -1);
            
            for(int testMove = 0; testMove < nextMoves.Count; testMove++)
            {
                if (assess(testBoard, testMove) > bestMove.y)
                {
                    bestMove = new Vector3(testMove, assess(testBoard, testMove));
                }
            }
            value += (int)bestMove.y;
        }
        else if((board[resulthole] == 0 && resulthole >= 6) && board[13-resulthole] != 0)
        {
            value += 1 + board[13 - resulthole];
        }
        return value;
    }

    List<int> legalMoveFinder(int[] board)
    {
        List<int> legalMoves = new List<int>();
        for (int i = 7; i < 13; i++)
        {
            if (board[i] > 0)
            {
                legalMoves.Add(i);
            }
        }
        return legalMoves;
    }

    public int mover(int[] board)
    {
        int score = board[13];
        int playerScore = board[6];
        List<int> legalMoves = legalMoveFinder(board);
        Vector3 bestMove = new Vector3(7, -1);
        for(int consider = 0; consider < legalMoves.Count; consider++)
        {
            if (assess(board, consider) > bestMove.y)
            {
                Debug.Log("What is this: " + legalMoves[consider]);
                bestMove = new Vector3(legalMoves[consider], assess(board, consider));
            }
        }
        return (int)bestMove.x;
    }
}
