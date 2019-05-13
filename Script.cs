using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Script : MonoBehaviour
{
    Ray lastClickLocation;
    bool tick;
    ArrayList[] stones;
    int player_turn;
    int ai_turn;
    int[] A;
    int[] B;
    public GameObject redStone;
    public GameObject blueStone;
    public GameObject yellowStone;
    public GameObject greenStone;
    int play;
    AI theAI = new AI();
    bool Win;

    // Start is called before the first frame update
    void Start()
    {
        Debug.Log("We Started");
        tick = false;
        player_turn = 0;
        ai_turn = 0;
        A = new int[14];
        B = new int[14];
        stones = new ArrayList[14];
        Win = false;
        A[0] =4;
        A[1] =4;
        A[2] =4;
        A[3] =4;
        A[4] =4;
        A[5] =4;
        A[6] =0;
        A[7] =4;
        A[8] =4;
        A[9] =4;
        A[10] =4;
        A[11] =4;
        A[12] =4;
        A[13] =0;
        B[0] = 0;
        B[1] = 0;
        B[2] = 0;
        B[3] = 0;
        B[4] = 0;
        B[5] = 0;
        B[6] = 0;
        B[7] = 0;
        B[8] = 0;
        B[9] = 0;
        B[10] = 0;
        B[11] = 0;
        B[12] = 0;
        B[13] = 0;
        for (int i = 0; i < 14; i++)
        {
            stones[i] = new ArrayList();
        }
        
    }

    void placeStones(int number, int pocketNumber, float xMin, float xMax, float yMin, float yMax)
    {
        int count = stones[pocketNumber].Count;
        for (int j = 0; j < count;j++)
        {
            Destroy((GameObject)stones[pocketNumber][j]);
        }
        float x, y;
        for (int i =0; i < number; i++)
        {
            x = Random.Range(xMin, xMax);
            y = Random.Range(yMin, yMax);
            int color = (int)Random.Range(0, 4);
            if(color==1)
                stones[pocketNumber].Add(Instantiate(redStone, new Vector3(x, y), Quaternion.identity));
            if(color==2)
                stones[pocketNumber].Add(Instantiate(blueStone, new Vector3(x, y), Quaternion.identity));
            if (color==3)
                stones[pocketNumber].Add(Instantiate(greenStone, new Vector3(x, y), Quaternion.identity));
            else
                stones[pocketNumber].Add(Instantiate(yellowStone, new Vector3(x, y), Quaternion.identity));
        }
    }


    int getPlay()
    {
        if (Input.GetMouseButtonDown(0))
        {
        lastClickLocation = Camera.main.ScreenPointToRay(Input.mousePosition);
        float x = lastClickLocation.origin.x;
            float y = lastClickLocation.origin.y;
        if (x > -6 && x < -5 && y > -3 && y < -2)
        {
            return 0;
        }
        if (x > -4 && x < -3 && y > -3 && y < -2)
        {
            return 1;
        }
        if (x > -1.8f && x < -.5f && y > -3 && y < -2)
        {
            return 2;
        }
        if (x > .5f && x < 1.8 && y > -3 && y < -2)
        {
            return 3;
        }
        if (x > 3 && x < 4 && y > -3 && y < -2)
        {
            return 4;
        }
        if (x > 5 && x < 6 && y > -3 && y < -2)
        {
            return 5;
        }
    }
        return -1;
    }

    void Update()
    {
       if (tick==false)
        {
            StartCoroutine("Tick");
        }
    }

    // Update is called once per frame
    IEnumerator Tick()
    {
        tick = true;
        if (!Win) 
        {
        Start:
            int counter = 0;
            if(A[0]!=B[0])
                placeStones(A[0], 0,-6.2f, -5.2f, -2, -3);
            if (A[1] != B[1])
                placeStones(A[1], 1,-4, -3, -2, -3);
            if (A[2] != B[2])
                placeStones(A[2], 2,-1.8f, -.5f, -2, -3);
            if (A[3] != B[3])
                placeStones(A[3], 3,.5f, 1.8f, -2, -3);
            if (A[4] != B[4])
                placeStones(A[4], 4,3, 4, -2, -3);
            if (A[5] != B[5])
                placeStones(A[5], 5,5.2f, 6.2f, -2, -3);
            if (A[6] != B[6])
                placeStones(A[6], 6, 9, 7.5f, -1, 1);
            if (A[7] != B[7])
                placeStones(A[7], 7,5.2f, 6.2f, 2, 3);
            if (A[8] != B[8])
                placeStones(A[8], 8, 3, 4, 2, 3);
            if (A[9] != B[9])
                placeStones(A[9], 9,.5f, 1.8f, 2, 3);
            if (A[10] != B[10])
                placeStones(A[10], 10, -1.8f, -.5f, 2, 3);
            if (A[11] != B[11])
                placeStones(A[11], 11,-4, -3, 2, 3);
            if (A[12] != B[12])
                placeStones(A[12], 12, -6.2f, -5.2f, 2, 3);
            if (A[13] != B[13])
                placeStones(A[13], 13, -9, -7.5f, -1, 1);
            
            for (int i = 0; i < 14; i++)
            {
                B[i] = A[i];
            }
            if (A[6] > 23)
            {
                Win = true;
            }
            if (A[13] > 23)
            {
                Win = true;
            }
            play = -1;
            Debug.Log("Your turn");
            while (play == -1)
            {
                play = getPlay();
                if (play != -1) {
                    if (A[play] == 0)
                    {
                    play = -1;
                    }
                }
                yield return null;
            }
            counter = A[play];
            A[play] = 0;
            for (int c = 1; c < counter + 1; c++)
            {
                if ((play + c) % 14 == 13)
                {
                    counter++;
                }
                else
                {
                    A[(play + c) % 14]++;
                }
            }

            if ((play + counter) % 14 == 6)
            {
                goto Start;
            }
            if (((play + counter) % 14 < 6))
            {
                if (A[(play + counter) % 14] == 1 && A[12 - ((play + counter) % 14)] != 0)
                {
                    int add = 1 + A[(12 - ((play + counter) % 14))];
                    A[12 - (play + counter) % 14] = 0;
                    A[(play + counter) % 14] = 0;
                    for (int k = 0; k < add; k++)
                    {
                        A[6]++;
                    }
                }
            }
            if (A[7] + A[8] + A[9] + A[10] + A[11] + A[12] == 0)
            {
                int stone = A[0] + A[1] + A[2] + A[3] + A[4] + A[5];
                A[0] = 0;
                A[1] = 0;
                A[2] = 0;
                A[3] = 0;
                A[4] = 0;
                A[5] = 0;
                A[13] = A[13] + stone;
                //player win
            }
        ai_repeat:
            if (A[0] != B[0])
                placeStones(A[0], 0, -6.2f, -5.2f, -2, -3);
            if (A[1] != B[1])
                placeStones(A[1], 1, -4, -3, -2, -3);
            if (A[2] != B[2])
                placeStones(A[2], 2, -1.8f, -.5f, -2, -3);
            if (A[3] != B[3])
                placeStones(A[3], 3, .5f, 1.8f, -2, -3);
            if (A[4] != B[4])
                placeStones(A[4], 4, 3, 4, -2, -3);
            if (A[5] != B[5])
                placeStones(A[5], 5, 5.2f, 6.2f, -2, -3);
            if (A[6] != B[6])
                placeStones(A[6], 6, 9, 7.5f, -1, 1);
            if (A[7] != B[7])
                placeStones(A[7], 7, 5.2f, 6.2f, 2, 3);
            if (A[8] != B[8])
                placeStones(A[8], 8, 3, 4, 2, 3);
            if (A[9] != B[9])
                placeStones(A[9], 9, .5f, 1.8f, 2, 3);
            if (A[10] != B[10])
                placeStones(A[10], 10, -1.8f, -.5f, 2, 3);
            if (A[11] != B[11])
                placeStones(A[11], 11, -4, -3, 2, 3);
            if (A[12] != B[12])
                placeStones(A[12], 12, -6.2f, -5.2f, 2, 3);
            if (A[13] != B[13])
                placeStones(A[13], 13, -9, -7.5f, -1, 1);
            yield return new WaitForSeconds(1);
            Debug.Log("Ai's turn");
            int AI = theAI.mover(A);
            Debug.Log("The move picked was " + AI);
            ai_turn++;
            int count = A[AI];
            A[AI] = 0;
            for (int c = 1; c < count + 1; c++)
            {
                if ((AI + c) % 14 != 6)
                {
                    //adds a stone to the bucket if its not the player score tray
                    A[(AI + c) % 14]++;
                }
                else
                {
                    count++;
                }
            }
            if ((AI + count) % 14 == 13)
            {
                //last stone went in score tray so ai gets another turn
                goto ai_repeat;
            }
            if ((((AI + count) % 14) > 6) && (((AI + count) % 14) < 13))
            { //if turn ends in own side
                if (A[(AI + count) % 14] == 1 && A[(12 - ((AI + count) % 14))] != 0)
                {
                    //and last stone is in an empty bucket across from a not empty bucket
                    //take the stones from both and add to score
                    int add = 1 + A[(12 - ((AI + count) % 14))];
                    A[(12 - (AI + count) % 14)] = 0;
                    //return board graphic from maeve
                    A[(AI + count) % 14] = 0;
                    //return board graphic from maeve
                    for (int k = 0; k < add; k++)
                    {
                        //return board graphic from maeve
                        A[13]++;
                    }
                }
            }
            if ((A[0] == 0 && A[1] == 0 && A[2] == 0 && A[3] == 0 && A[4] == 0 && A[5] == 0))
            {
                //if no stones on player side,  add ai stones to their score and exit
                int stone = A[7] + A[8] + A[9] + A[10] + A[11] + A[12];
                A[7] = 0;
                A[8] = 0;
                A[9] = 0;
                A[10] = 0;
                A[11] = 0;
                A[12] = 0;
                for (int l = 0; l < stone; l++)
                {
                    //return board graphic from maeve
                    A[13]++;
                }
                Win = true;
            }
        }
        else
        {
            Debug.Log("Win!");
        }
        tick = false;
    }
    
}
