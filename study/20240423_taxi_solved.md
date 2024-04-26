### [김민재] #1

```cpp
#include <stdio.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define ABS(x) (((x) > 0) ? (x) : -(x))
#define MAX_SIZE 100000

/* These constant variables will NOT be changed */
static constexpr int MAX_DRIVER_COUNT = 100;
static constexpr int MAX_PASSENGER_COUNT = 10'000;

bool isArrived[MAX_PASSENGER_COUNT];
int numberOfDriver;
int numberOfPassenger;
long long maxDriverScore;

struct Pair
{
    int key;
    long long value;
};

struct PriorityQueue
{
    Pair heap[MAX_SIZE];
    int heapSize = 0;

    void heapInit()
    {
       heapSize = 0;
    }

    void heapPush(int key, long long value)
    {
       heap[heapSize].key = key;
       heap[heapSize].value = value;
       int current = heapSize;
       while (current > 0 && heap[current].value < heap[(current - 1) / 2].value)
       {
          Pair temp = heap[(current - 1) / 2];
          heap[(current - 1) / 2] = heap[current];
          heap[current] = temp;
          current = (current - 1) / 2;
       }
       heapSize = heapSize + 1;
    }

    Pair heapPop()
    {
       Pair value = heap[0];
       heapSize = heapSize - 1;

       heap[0] = heap[heapSize];

       int current = 0;
       while (current * 2 + 1 < heapSize)
       {
          int child;
          if (current * 2 + 2 == heapSize)
             child = current * 2 + 1;
          else
             child = heap[current * 2 + 1].value < heap[current * 2 + 2].value ? current * 2 + 1 : current * 2 + 2;

          if (heap[current].value < heap[child].value)
             break;

          Pair temp = heap[current];
          heap[current] = heap[child];
          heap[child] = temp;
          current = child;
       }
       return value;
    }
};

struct Coordinate
{
    int y, x;
};

struct Passenger
{
    Coordinate departure;
    Coordinate arrival;
};

struct Passengers
{
    int id[200];
    int size = 0;

    void clear()
    {
       size = 0;
    }

    void add(int passengerId)
    {
       id[size] = passengerId;
       size += 1;
    }
};

extern bool assign_driver(int driverID, int passengerSize, int passengerIDs[]);

Passengers passengersClassifiedAsDeparture[100][100];
Passenger passenger[MAX_PASSENGER_COUNT + MAX_DRIVER_COUNT];

struct Driver
{
    Coordinate coordinate;
    PriorityQueue nextPassengers;
    int currentPassenger;
    int passengerSize = 0;
    int passengerIDs[MAX_PASSENGER_COUNT];
    long long score;

    void init(Coordinate coordinate)
    {
       score = 0;
       this->coordinate = coordinate;
       passengerSize = 0;
       nextPassengers.heapInit();
    }

    long long getIncrement()
    {
       int passengerId = nextPassengers.heap[0].key;
       Coordinate pickUp = passenger[passengerId].departure;
       Coordinate dropOff = passenger[passengerId].arrival;
       return ABS(pickUp.y - coordinate.y) + ABS(pickUp.x - coordinate.x) + ABS(dropOff.y - pickUp.y) + ABS(dropOff.x - pickUp.x);
    }

    void printAssignScore()
    {
       int passengerId = nextPassengers.heap[0].key;
       Coordinate pickUp = passenger[passengerId].departure;
       Coordinate dropOff = passenger[passengerId].arrival;
       long long pickUpScore = ABS(pickUp.y - coordinate.y) + ABS(pickUp.x - coordinate.x);
       long long dropScore = ABS(dropOff.y - pickUp.y) + ABS(dropOff.x - pickUp.x);
       printf(" pickUp: %10lld  |  drop score: %10lld \n", pickUpScore, dropScore);
    }

    void assign()
    {
       //printAssignScore();
       currentPassenger = nextPassengers.heap[0].key;
       score += getIncrement();
       passengerIDs[passengerSize++] = currentPassenger;
       coordinate = passenger[currentPassenger].arrival;
       nextPassengers.heapInit();
       isArrived[currentPassenger] = true;
       maxDriverScore = MAX(maxDriverScore, score);
    }

    void addToQueue(int range)
    {
       int py = coordinate.y / 10000;
       int px = coordinate.x / 10000;
       int sy = py - range < 0 ? 0 : py - range;
       int ey = py + range > 100 ? 100 : py + range;
       int sx = px - range < 0 ? 0 : px - range;
       int ex = px + range > 100 ? 100 : px + range;

       for (int i = sy; i < ey; ++i)
       {
          for (int j = sx; j < ex; ++j)
          {
             for (int k = 0; k < passengersClassifiedAsDeparture[i][j].size; ++k)
             {
                int nextPassenger = passengersClassifiedAsDeparture[i][j].id[k];

                if (isArrived[nextPassenger])
                   continue;

                Coordinate departure = passenger[nextPassenger].departure;
                long long distance = ABS(coordinate.y - departure.y) + ABS(coordinate.x - departure.x);
                nextPassengers.heapPush(nextPassenger, distance);
             }
          }
       }

       if (nextPassengers.heapSize == 0)
       {
          addToQueue(range + 5);
       }
    }

    void removeArrivedPassenger()
    {
       while (nextPassengers.heapSize >0 && isArrived[nextPassengers.heap[0].key])
       {
          nextPassengers.heapPop();
       }
    }

    void setNextPassengers()
    {
       if (nextPassengers.heapSize == 0)
          addToQueue(5);
    }
};

Driver driver[MAX_DRIVER_COUNT + MAX_DRIVER_COUNT];

void initGlobalVariable(int M, Coordinate* mDriver, int K, Passenger* mPassenger)
{
    maxDriverScore = 0;
    numberOfDriver = M;
    numberOfPassenger = K;

    for (int i = 0; i < numberOfPassenger; ++i)
    {
       passenger[i].departure = mPassenger[i].departure;
       passenger[i].arrival = mPassenger[i].arrival;
       isArrived[i] = false;

    }

    for (int i = 0; i < numberOfDriver; ++i)
    {
       int passengerId = numberOfPassenger + i;
       driver[i].init(mDriver[i]);
       driver[i].currentPassenger = passengerId;
       passenger[passengerId].departure.y = -1;
       passenger[passengerId].departure.x = -1;
       passenger[passengerId].arrival = mDriver[i];
       isArrived[passengerId] = true;
    }
}

void clearClassifiedPassengers()
{
    for (int i = 0; i<100; i++)
    {
       for (int j = 0; j<100; j++)
       {
          passengersClassifiedAsDeparture[i][j].clear();
       }
    }
}

void classifyPassengers()
{
    for (int i = 0; i < numberOfPassenger; ++i)
    {
       Coordinate departure = passenger[i].departure;
       passengersClassifiedAsDeparture[departure.y / 10000][departure.x / 10000].add(i);
    }
}


void printDriverScore()
{
    for (int i = 0; i < numberOfDriver; ++i)
    {
       printf(" %2d Driver score: %3d \n", i, driver[i].score);
    }
    printf(" Max Driver score: %3d \n", maxDriverScore);
    printf(" --------------------------------------- \n");
    
}

void assign()
{
    while (numberOfPassenger > 0)
    {
       numberOfPassenger -= 1;
       for (int j = 0; j < numberOfDriver; ++j)
       {
          driver[j].removeArrivedPassenger();
          driver[j].setNextPassengers();
          int k = 0;
       }

       int driverId = 0;
       long long minPickUpDist = driver[0].nextPassengers.heap[0].value;
       long long minPickUpDist1 = driver[0].nextPassengers.heap[1].value;
       long long minPickUpDist2 = driver[0].nextPassengers.heap[2].value;
       
       //long long minIncrementOfMaxDriverScore = MAX(0, driver[0].score + driver[0].getIncrement() - maxDriverScore);
       long long minIncrementOfMaxDriverScore = driver[0].score + driver[0].getIncrement() - maxDriverScore;

       for (int j = 1; j < numberOfDriver; ++j)
       {
          long long pickUpDist = driver[j].nextPassengers.heap[0].value;
          //long long incrementOfMaxDriverScore = MAX(0, driver[j].score + driver[j].getIncrement() - maxDriverScore);
          long long incrementOfMaxDriverScore = driver[j].score + driver[j].getIncrement() - maxDriverScore;

          if (incrementOfMaxDriverScore >= minIncrementOfMaxDriverScore)
             continue;
          if(incrementOfMaxDriverScore == 0 && pickUpDist >= minPickUpDist)
             continue;

          driverId = j;
          minPickUpDist = pickUpDist;
          minIncrementOfMaxDriverScore = incrementOfMaxDriverScore;
       }

       driver[driverId].assign();
       //printDriverScore();
       int k = 0;
    }
}

void assignDriver()
{
    for (int i = 0; i < numberOfDriver; ++i)
    {
       assign_driver(i, driver[i].passengerSize, driver[i].passengerIDs);
    }
}


void run(int N, int M, Coordinate mDriver[], int K, Passenger mPassenger[])
{
    initGlobalVariable(M, mDriver, K, mPassenger);
    clearClassifiedPassengers();
    classifyPassengers();
    assign();
    assignDriver();
    //printDriverScore();
    int k = 0;
}
```

### [박종환]

- 택시 운행 시마다 score 를 저장하여 매번 택시 운행을 위해 가장 score 상승이 낮은 택시-손님 페어를 찾아서 운행하였습니다.
- 다만 매번 가장 낮은 score 를 찾으려다 보니 시간이 7~8초가 걸려는 문제가 있습니다.
- SCORE: 436,067,446
- elapsed: 7.954362

```cpp
#define ABS(x) (((x) > 0) ? (x) : -(x))

struct Coordinate
{
    int y, x;
};

struct Passenger
{
    Coordinate departure;
    Coordinate arrival;
};

static const int MAX_PASSENGER_COUNT = 10'000;
static const int MAX_DRIVER_COUNT = 100;

int max(int a, int b) { return a > b ? a : b; }
int getDistance(Coordinate a, Coordinate b)
{
    return ABS(a.x - b.x) + ABS(a.y - b.y);
}

extern bool assign_driver(int driverID, int passengerSize, int passengerIDs[]);

struct Node
{
    int distance;
    int id;
};

class Heap
{
public:
    int length;
    Node arr[MAX_PASSENGER_COUNT];

    void init() { length = 0; }

    bool compare(int parent, int child)
    {
        if (arr[parent].distance > arr[child].distance)
        {
            return true;
        }
        return false;
    }

    void push(int dist, int id)
    {
        Node node = {dist, id};

        int idx = length;
        arr[length++] = node;

        while ((idx - 1) / 2 >= 0 && compare((idx - 1) / 2, idx))
        {
            Node temp = arr[idx];
            arr[idx] = arr[(idx - 1) / 2];
            arr[(idx - 1) / 2] = temp;
            idx = (idx - 1) / 2;
        }
    }

    Node pop()
    {
        Node ans = arr[0];
        arr[0] = arr[--length];

        int idx = 0;
        int left, right, child;

        while (2 * idx + 1 < length)
        {
            left = 2 * idx + 1;
            right = 2 * idx + 2;

            if (right < length)
                if (compare(left, right))
                    child = right;
                else
                    child = left;
            else
                child = left;

            if (compare(idx, child))
            {
                Node temp = arr[idx];
                arr[idx] = arr[child];
                arr[child] = temp;
                idx = child;
            }
            else
            {
                break;
            }
        }

        return ans;
    }
};

Heap pQueue[MAX_DRIVER_COUNT];
bool finished[MAX_PASSENGER_COUNT];
int passengerSize[MAX_DRIVER_COUNT];
int passengerIDs[MAX_DRIVER_COUNT][MAX_PASSENGER_COUNT];
Coordinate driverLocation[MAX_DRIVER_COUNT];
int score[MAX_DRIVER_COUNT];

void run(int N, int M, Coordinate mDriver[], int K, Passenger mPassenger[])
{

    //    for (int driver = 0; driver < M; driver++)
    //    {
    //        passengerSize[driver] = 0;
    //
    //        driverLocation[driver] = mDriver[driver];
    //
    //        score[driver] = 0;
    //
    //        pQueue[driver].init();
    //    }

    for (int driver = 0; driver < M; driver++)
    {
        passengerSize[driver] = 0;

        driverLocation[driver] = mDriver[driver];

        score[driver] = 0;

        pQueue[driver].init();

        for (int passenger = 0; passenger < K; passenger++)
        {
            int dist = getDistance(mDriver[driver], mPassenger[passenger].departure);

            pQueue[driver].push(dist, passenger);

            if (driver == 0)
            {
                finished[passenger] = 0;
            }
        }
    }

    int cnt = 0;

    while (cnt < K)
    {
        int curr_driver = -1;
        int min_dist = 4 * N * 100;

        for (int driver = 0; driver < M; driver++)
        {
            int wait_passenger = pQueue[driver].arr[0].id;
            int travel = getDistance(mPassenger[wait_passenger].departure, mPassenger[wait_passenger].arrival);

            if (pQueue[driver].arr[0].distance + score[driver] + travel < min_dist)
            {
                min_dist = pQueue[driver].arr[0].distance + score[driver] + travel;
                curr_driver = driver;
            }
        }

        Node curr = pQueue[curr_driver].pop();
        int passenger = curr.id;

        while (finished[passenger])
        {
            curr = pQueue[curr_driver].pop();
            passenger = curr.id;
        }

        passengerIDs[curr_driver][passengerSize[curr_driver]++] = passenger;

        score[curr_driver] += 
            (getDistance(mPassenger[passenger].departure, mPassenger[passenger].arrival) + getDistance(driverLocation[curr_driver], 
             mPassenger[passenger].departure));

        driverLocation[curr_driver] = mPassenger[passenger].arrival;
        finished[passenger] = 1;
        cnt++;

        pQueue[curr_driver].init();

        for (int p = 0; p < K; p++)
        {
            if (!finished[p])
            {
                int dist = getDistance(driverLocation[curr_driver], mPassenger[p].departure);

                pQueue[curr_driver].push(dist, p);
            }
        }
    }

    //    for (int passenger = 0; passenger < K; passenger++)
    //    {
    //        int min_dist = 4 * N;
    //
    //        int close_driver = -1;
    //
    //        int min_score = 4 * N * 100;
    //
    //        for (int driver = 0; driver < M; driver++)
    //        {
    //            int dist = getDistance(mPassenger[passenger].departure, driverLocation[driver]);
    //
    //            if (dist < min_dist && score[driver] == 0)
    //            {
    //                min_dist = dist;
    //                close_driver = driver;
    //            }
    //            else if (dist < min_dist && score[driver] < min_score && score[driver] > 0)
    //            {
    //                min_dist = dist;
    //                close_driver = driver;
    //                min_score = score[driver];
    //            }
    //
    //        }
    //
    //        passengerIDs[close_driver][passengerSize[close_driver]++] = passenger;
    //
    //        score[close_driver] += (getDistance(mPassenger[passenger].departure, mPassenger[passenger].arrival)
    //                                + getDistance(driverLocation[close_driver], mPassenger[passenger].departure));
    //
    //        driverLocation[close_driver] = mPassenger[passenger].arrival;
    //
    //    }


    for (int driver = 0; driver < M; driver++)
    {
        assign_driver(driver, passengerSize[driver], passengerIDs[driver]);
    }

    return;
}

```


### [백승재]

- 점수 : 440'813'780

1. 맵을 100 개의 구역으로 나눔 (초기 배정에 승객 출발위치 대략 나눔)
   ((passengerList[i].departure.y / MAP_SPLIT) * 10) + (passengerList[i].departure.x / MAP_SPLIT);
2. 모든 택시에 대해 근처 구역에서 한번은 가까운 승객 배정
3. 이동 거리가 가장 낮은 택시에 근처 구역에서 가장 가까운 승객 배정
   없는 경우 전체 승객중에 검색
 (추가 아이디어? 3번에서 낮은 점수 택시를 5~10개 뽑아서 전체 검색, 가장 높은 점수 택시를 다른 택시의 승객과 랜덤하게 바꿔서 점수비교/변경)

```cpp
#include<malloc.h>

#define NULL 0

#define MAP_SIZE 1'000'000

#define MAP_SPLIT 100'000

#define MAX_DRIVER_COUNT 100

#define MAX_PASSENGER_COUNT 10'000

#define MAX_SIZE 100



#define ABS(x) (((x) > 0) ? (x) : -(x))



struct Coordinate

{

	int y, x;

};





struct Passenger

{

	Coordinate departure;

	Coordinate arrival;

};





typedef struct ListNode

{

	int data;

	struct ListNode* prev;

	struct ListNode* next;

};



ListNode* list_create(int _data)

{

	ListNode* node = (ListNode*)malloc(sizeof(ListNode));



	node->prev = NULL;

	node->next = NULL;



	node->data = _data;



	return node;

}



ListNode* list_insert(ListNode* _head, ListNode* new_node)

{

	ListNode* next = _head->next;



	_head->next = new_node;

	new_node->next = next;

	new_node->prev = _head;



	if (next != NULL)

	{

		next->prev = new_node;

	}



	return new_node;

}



int list_erase(ListNode* head, int _data)

{

	ListNode* it = head->next;

	int ret = 0;



	while (it != NULL)

	{

		if (it->data == _data)

		{

			ListNode* prev = it->prev;

			ListNode* next = it->next;

			ListNode* tmp = it;

			it = it->next;



			prev->next = next;

			if (next != NULL)

			{

				next->prev = prev;

			}



			free(tmp);

			ret++;

		}

		else

		{

			it = it->next;

		}

	}



	return ret;

}





struct HEAP_ITEM

{

	int value;

	int id;

};



struct HEAP_ASC

{

	HEAP_ITEM heap[MAX_SIZE];

	int heapSize = 0;



	void heapInit(void)

	{

		heapSize = 0;

	}



	int heapPush(int value, int id)

	{

		if (heapSize + 1 > MAX_SIZE)

		{

			return 0;

		}



		heap[heapSize].value = value;

		heap[heapSize].id = id;



		int current = heapSize;

		while (current > 0 && heap[current].value < heap[(current - 1) / 2].value)

		{

			HEAP_ITEM temp = heap[(current - 1) / 2];

			heap[(current - 1) / 2] = heap[current];

			heap[current] = temp;

			current = (current - 1) / 2;

		}



		heapSize = heapSize + 1;



		return 1;

	}



	int heapPop(int *value, int *id)

	{

		if (heapSize <= 0)

		{

			return -1;

		}



		*value = heap[0].value;

		*id = heap[0].id;

		heapSize = heapSize - 1;



		heap[0] = heap[heapSize];



		int current = 0;

		while (current * 2 + 1 < heapSize)

		{

			int child;

			if (current * 2 + 2 == heapSize)

			{

				child = current * 2 + 1;

			}

			else

			{

				child = heap[current * 2 + 1].value < heap[current * 2 + 2].value ? current * 2 + 1 : current * 2 + 2;

			}



			if (heap[current].value < heap[child].value)

			{

				break;

			}



			HEAP_ITEM temp = heap[current];

			heap[current] = heap[child];

			heap[child] = temp;



			current = child;

		}

		return 1;

	}

};



struct HEAP_DESC

{

	HEAP_ITEM heap[MAX_SIZE];

	int heapSize = 0;



	void heapInit(void)

	{

		heapSize = 0;

	}



	int heapPush(int value, int id)

	{

		if (heapSize + 1 > MAX_SIZE)

		{

			return 0;

		}



		heap[heapSize].value = value;

		heap[heapSize].id = id;



		int current = heapSize;

		while (current > 0 && heap[current].value > heap[(current - 1) / 2].value)

		{

			HEAP_ITEM temp = heap[(current - 1) / 2];

			heap[(current - 1) / 2] = heap[current];

			heap[current] = temp;

			current = (current - 1) / 2;

		}



		heapSize = heapSize + 1;



		return 1;

	}



	int heapPop(int *value, int *id)

	{

		if (heapSize <= 0)

		{

			return -1;

		}



		*value = heap[0].value;

		*id = heap[0].id;

		heapSize = heapSize - 1;



		heap[0] = heap[heapSize];



		int current = 0;

		while (current * 2 + 1 < heapSize)

		{

			int child;

			if (current * 2 + 2 == heapSize)

			{

				child = current * 2 + 1;

			}

			else

			{

				child = heap[current * 2 + 1].value > heap[current * 2 + 2].value ? current * 2 + 1 : current * 2 + 2;

			}



			if (heap[current].value > heap[child].value)

			{

				break;

			}



			HEAP_ITEM temp = heap[current];

			heap[current] = heap[child];

			heap[child] = temp;



			current = child;

		}

		return 1;

	}

};



extern bool assign_driver(int driverID, int passengerSize, int passengerIDs[]);





void run(int N, int M, Coordinate mDriver[], int K, Passenger mPassenger[])

{

	int driverCnt = M;

	Coordinate driverList[MAX_DRIVER_COUNT];

	long long score[MAX_DRIVER_COUNT];

	int passengerCnt = K;

	Passenger passengerList[MAX_PASSENGER_COUNT];

	int passengerCheck[MAX_PASSENGER_COUNT];



	ListNode* head_taxi[100];

	HEAP_ASC _heapASC;

	_heapASC.heapInit();

	for (int i = 0; i < driverCnt; i++)

	{

		driverList[i] = mDriver[i];

		score[i] = 0;

		head_taxi[i] = list_create(NULL);

		//_heapASC.heapPush(score[i], i);

	}





	ListNode* head_passenger[100];

	int count_passenger[100] = { 0, };

	for (int i = 0; i < 100; i++)

		head_passenger[i] = list_create(NULL);

	int _id = 0;

	for (int i = 0; i < passengerCnt; i++)

	{

		passengerList[i] = mPassenger[i];

		passengerCheck[i] = 1;



		ListNode* node = list_create(i);

		_id = ((passengerList[i].departure.y / MAP_SPLIT) * 10) + (passengerList[i].departure.x / MAP_SPLIT);

		list_insert(head_passenger[_id], node);

		count_passenger[_id]++;

	}





	int _sign = 0;

	int taxiId = 0;

	int taxiValue = 0;

	int passengerId = -1;

	int bufId = 0;

	int maxLen = 0x7fffffff;

	int bufLen = 0x7fffffff;

	int loop[9] = { 0, 1, -1, 10, -10, 11, -9, 9, -11 };

	int realId = 0;



	//한번은 전부 검색해서 가까운걸로 배당.

	for (int i = 0; i < driverCnt; i++)

	{

		taxiId = i;

		taxiValue = 0;



		passengerId = -1;

		maxLen = 0x7fffffff;



		for (int i = 0; i < 9; i++)

		{

			realId = _id + loop[i];



			if (0 <= realId && 100 > realId)

			{

				ListNode* tmp = head_passenger[realId]->next;

				while (tmp != NULL)

				{

					bufId = tmp->data;

					if (passengerCheck[bufId] > 0)

					{

						bufLen = ABS(passengerList[bufId].departure.y - driverList[taxiId].y) + ABS(passengerList[bufId].departure.x - driverList[taxiId].x);

						if (maxLen > bufLen)

						{

							maxLen = bufLen;

							passengerId = bufId;

						}

					}

					tmp = tmp->next;

				}

			}

		}



		if (passengerId == -1)

		{

			for (int i = 0; i < passengerCnt; i++)

			{

				bufId = i;

				if (passengerCheck[bufId] > 0)

				{

					bufLen = ABS(passengerList[bufId].departure.y - driverList[taxiId].y) + ABS(passengerList[bufId].departure.x - driverList[taxiId].x);

					if (maxLen > bufLen)

					{

						maxLen = bufLen;

						passengerId = bufId;

					}

				}

			}

		}



		if (passengerId != -1)

		{

			driverList[taxiId] = passengerList[passengerId].arrival;

			passengerCheck[passengerId] = 0;

			score[taxiId] = taxiValue + maxLen + ABS(passengerList[passengerId].arrival.y - passengerList[passengerId].departure.y) + ABS(passengerList[passengerId].arrival.x - passengerList[passengerId].departure.x); //maxLen = 이동거리.. 



			ListNode* node = list_create(passengerId);

			list_insert(head_taxi[taxiId], node);

			_heapASC.heapPush(score[taxiId], taxiId);

			_sign++;

		}

	}



	//가장 점수가 낮은 택시기사를 뽑아 가장 가까운 승객 배정

	while (_sign < passengerCnt)

	{

		_heapASC.heapPop(&taxiValue, &taxiId);

		_id = ((driverList[taxiId].y / MAP_SPLIT) * 10) + (driverList[taxiId].x / MAP_SPLIT);



		passengerId = -1;

		maxLen = 0x7fffffff;



		for (int i = 0; i < 9; i++)

		{

			realId = _id + loop[i];



			if (0 <= realId && 100 > realId)

			{

				ListNode* tmp = head_passenger[realId]->next;

				while (tmp != NULL)

				{

					bufId = tmp->data;

					if (passengerCheck[bufId] > 0)

					{

						bufLen = ABS(passengerList[bufId].departure.y - driverList[taxiId].y) + ABS(passengerList[bufId].departure.x - driverList[taxiId].x);

						if (maxLen > bufLen)

						{

							maxLen = bufLen;

							passengerId = bufId;

						}

					}

					tmp = tmp->next;

				}

			}

		}



		if (passengerId == -1)

		{

			for (int i = 0; i < passengerCnt; i++)

			{

				bufId = i;

				if (passengerCheck[bufId] > 0)

				{

					bufLen = ABS(passengerList[bufId].departure.y - driverList[taxiId].y) + ABS(passengerList[bufId].departure.x - driverList[taxiId].x);

					if (maxLen > bufLen)

					{

						maxLen = bufLen;

						passengerId = bufId;

					}

				}

			}

		}



		if (passengerId != -1)

		{



			driverList[taxiId] = passengerList[passengerId].arrival;

			passengerCheck[passengerId] = 0;

			score[taxiId] = taxiValue + maxLen + ABS(passengerList[passengerId].arrival.y - passengerList[passengerId].departure.y) + ABS(passengerList[passengerId].arrival.x - passengerList[passengerId].departure.x); //maxLen = 이동거리.. 



			ListNode* node = list_create(passengerId);

			list_insert(head_taxi[taxiId], node);

			_heapASC.heapPush(score[taxiId], taxiId);

			_sign++;

		}

	}



	int passengerSize = 0;

	int reverse = 0;

	int passengerIDs[MAX_PASSENGER_COUNT];

	bool assign_driver(int driverID, int passengerSize, int passengerIDs[]);

	for (int i = 0; i < driverCnt; i++)

	{

		passengerSize = 0;

		ListNode* tmp = head_taxi[i]->next;

		while (tmp != NULL)

		{

			//passengerIDs[passengerSize] = tmp->data;

			passengerSize++;

			tmp = tmp->next;

		}



		tmp = head_taxi[i]->next;

		reverse = passengerSize;

		while (tmp != NULL)

		{
			passengerIDs[reverse - 1] = tmp->data;
			reverse--;
			tmp = tmp->next;

		}

		assign_driver(i, passengerSize, passengerIDs);

	}
	return;
}
```

### [main]

```cpp
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <stdio.h>
#include <time.h>

static unsigned long long seed = 5;

static int pseudo_rand(void)
{
    seed = seed * 25214903917ULL + 11ULL;
    return (seed >> 16) & 0x3fffffff;
}


static constexpr int MAX_TC = 5;

/* These constant variables will NOT be changed */
static constexpr int MAP_SIZE = 1'000'000;
static constexpr int MAX_DRIVER_COUNT = 100;
static constexpr int MAX_PASSENGER_COUNT = 10'000;
static constexpr long long PENALTY = 10'000'000'000'000LL;

struct Coordinate
{
    int y, x;
};


struct Passenger
{
    Coordinate departure;
    Coordinate arrival;
};


extern void run(int, int, Coordinate [], int, Passenger []);

#define ABS(x) (((x) > 0) ? (x) : -(x))


static int driverCnt;
static Coordinate driverList[MAX_DRIVER_COUNT];
static Coordinate driverList_bak[MAX_DRIVER_COUNT];
static int passengerCnt;
static Passenger passengerList[MAX_PASSENGER_COUNT];
static Passenger passengerList_bak[MAX_PASSENGER_COUNT];
static int isFinished[MAX_PASSENGER_COUNT];
static int assignList[MAX_DRIVER_COUNT][MAX_PASSENGER_COUNT];
static int assignListSize[MAX_DRIVER_COUNT];

static long long SCORE = 0;


bool assign_driver(int driverID, int passengerSize, int passengerIDs[])
{
    if (driverID < 0 || driverID >= driverCnt)
        return false;

    if (passengerSize < 0 || passengerSize > MAX_PASSENGER_COUNT)
        return false;

    for (int i = 0; i < passengerSize; i++)
    {
        if (passengerIDs[i] < 0 || passengerIDs[i] >= passengerCnt)
            return false;
    }

    for (int i = 0; i < passengerSize; i++)
    {
        assignList[driverID][i] = passengerIDs[i];
    }

    assignListSize[driverID] = passengerSize;

    return true;
}


static void make_tc()
{
    driverCnt = pseudo_rand() % 50 + 51;
    passengerCnt = pseudo_rand() % 5000 + 5001;

    for (int i = 0; i < driverCnt; i++)
    {
        driverList[i].y = driverList_bak[i].y = pseudo_rand() % MAP_SIZE;
        driverList[i].x = driverList_bak[i].x = pseudo_rand() % MAP_SIZE;
        assignListSize[i] = 0;
    }

    for (int i = 0; i < passengerCnt; i++)
    {
        passengerList[i].departure.y = passengerList_bak[i].departure.y = pseudo_rand() % MAP_SIZE;
        passengerList[i].departure.x = passengerList_bak[i].departure.x = pseudo_rand() % MAP_SIZE;
        passengerList[i].arrival.y = passengerList_bak[i].arrival.y = pseudo_rand() % MAP_SIZE;
        passengerList[i].arrival.x = passengerList_bak[i].arrival.x = pseudo_rand() % MAP_SIZE;
        isFinished[i] = 0;
    }
}

static bool verify()
{
    long long maxTestCaseScore = 0;
    long long totalPassengerScore = 0;
    long long totalPickUpScore = 0;

    for (int i = 0; i < driverCnt; i++)
    {
        Coordinate driverPos = driverList[i];
        long long score = 0;

        long long passengerScore = 0;
        long long pickUpScore = 0;

        for (int j = 0; j < assignListSize[i]; j++)
        {
            int passengerID = assignList[i][j];
            Coordinate pickUp = passengerList[passengerID].departure;
            Coordinate dropOff = passengerList[passengerID].arrival;

            if (isFinished[passengerID] == 1)
                return false;

            score += ABS(pickUp.y - driverPos.y) + ABS(pickUp.x - driverPos.x) + ABS(dropOff.y - pickUp.y) + ABS(dropOff.x - pickUp.x);

            pickUpScore += ABS(pickUp.y - driverPos.y) + ABS(pickUp.x - driverPos.x);
            passengerScore += ABS(dropOff.y - pickUp.y) + ABS(dropOff.x - pickUp.x);
            //score += ABS(dropOff.y - pickUp.y) + ABS(dropOff.x - pickUp.x);
            driverPos = dropOff;
            isFinished[passengerID] = 1;
        }

        if (maxTestCaseScore < score)
            maxTestCaseScore = score;

        totalPickUpScore += pickUpScore;
        totalPassengerScore += passengerScore;
    }

    for (int i = 0; i < passengerCnt; i++)
    {
        if (isFinished[i] == 0)
        {
            return false;
        }
    }

    //printf("Total Passenger SCORE: %12lld\n", totalPassengerScore);
    //printf("         Driver Count: %12d\n", driverCnt);

    //printf("   Total PickUp SCORE: %12lld\n", totalPickUpScore);
    printf("  Min Passenger SCORE: %12lld\n", (totalPassengerScore) / driverCnt);
    printf("     Min Driver SCORE: %12lld\n", (totalPassengerScore + totalPickUpScore) / driverCnt);
    printf("     Max Driver SCORE: %12lld\n", maxTestCaseScore);
    printf("-------------------------------------\n");
    SCORE += maxTestCaseScore;
    return true;
}

int main()
{
    clock_t start = clock();
    setbuf(stdout, nullptr);

    for (int tc = 0; tc < MAX_TC; tc++)
    {
        printf("TestCase: %d\n", tc);
        make_tc();
        run(MAP_SIZE, driverCnt, driverList_bak, passengerCnt, passengerList_bak);

        if (verify() == false)
        {
            printf("SCORE: %lld\n", PENALTY);
            //return 0;
        }
    }

    printf("SCORE: %lld\n", SCORE);
    printf("RESULT : %dms\n", (clock() - start) / (CLOCKS_PER_SEC / 1000));
    return 0;
}
```
