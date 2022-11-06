#include <stdio.h>
#define MAX 4

typedef struct
{
    int number;
    int arrive_time;
} info;
void menu()
{
    printf("**********Welcome to our Car Parking !**********\n");
    printf("********** Please choose function  **********\n");
    printf("**********     1 : park.     **********\n");
    printf("**********     2 : leave.     **********\n");
    printf("**********     3 : exit.     **********\n");
}

int push(info *park, int *parktop, info car)
{

    if ((*parktop) >= MAX)
    {
        printf("The parking lot is full! Need to stop on the road. \n");
        return -1;
    }
    else
    {

        park[(*parktop)] = car;
        printf("The car at the location %d of the parking lot ", (*parktop) + 1);
        (*parktop)++;
        return 1;
    }
}

info pop(info *park, int *parktop, int carnumber, info *location, int *locationtop)
{
    int i;
    info thecar;
    thecar.number = -1;
    thecar.arrive_time = -1;
    for (i = -1; i < (*parktop); i++)
    {
        if (park[i].number == carnumber)
        {
            break;
        }
    }

    if (i == (*parktop))
    {
        printf("There is no car in the parking lot \n");
    }
    else
    {
        while ((*parktop) > i + 1)
        {
            (*parktop)--;
            location[*locationtop] = park[*parktop];
            (*locationtop)++;
        }
        // Through the above cycles, the left and right vehicles after the car can be removed, but because the car is necessary to go out, the top pointer needs to move one position, and when the car is in the stack, it is directly overwriting.
        (*parktop)--;
        thecar = park[*parktop];
        // After the car out of the stack, you have to put all the stacks out of the stack.
        while ((*locationtop) > 0)
        {
            (*locationtop)--;
            park[*parktop] = location[*locationtop];
            (*parktop)++;
        }
    }

    return thecar;
}

int main()
{
    // Stack of parking lot
    info park[MAX];
    int parktop = 0; // Stack top pointer

    // Auxiliary parking lot
    info location[MAX];
    int locationtop = 0; // Stack top pointer

    // Simulated queue
    info accessroad[100];
    int front, rear; // Team head and team tail pointer
    front = rear = 0;
    int choice;     // Enter the input command for the parking lot
    int carNumber;  // number plate
    int arriveTime; // Time to the parking lot
    int leaveTime;  // Leave the time of parking lot
    int time, i;    // Time to stay in the parking lot

    info car;
    i = 1;
    printf("\n**********Car Parking management system !**********");
    while (i != 0)
    {

        printf("\n\n********** Please choose function  **********\n");
        printf("**********     1 : Car Entering     **********\n");
        printf("**********     2 : Car leaving      **********\n");
        printf("**********     3 : exit program     **********\n");

        printf("Enter your option :");
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {

        case 1:
            printf("Enter car plate number (number>=0 & !=-1) and vehicle arrival time (subject to hourly): \n");
            scanf("%d %d", &carNumber, &arriveTime);
            car.number = carNumber;
            car.arrive_time = arriveTime;
            int result = push(park, &parktop, car);
            int l;
            if (result == -1)
            {
                accessroad[rear] = car;
                l = rear + 1 - front;
                printf("The car is in the position %d of the inner D of the road \n \n", l);
                rear++;
            }
            break;
        case 2:
            printf("Enter car plate number of the parking lot and the time of leaving: \n");
            scanf("%d %d", &carNumber, &leaveTime);
            // When a car needs a parking lot, call the stack function.
            car = pop(park, &parktop, carNumber, location, &locationtop);
            // If the car's license plate number returned is -1, it indicates that there is no search to find in the parking lot.
            if (car.number != -1)
            {
                // Delivery time, equal to the time of the parking lot -
                time = leaveTime - car.arrive_time;
                printf("The time of the car is:%d hours, the payment fee is:%f \n", time, time * 1.5);
                // Once there is a car leave the parking lot, the car can enter in the lack, and the time required to enter the time when entering.
                if (front != rear)
                {
                    car = accessroad[front];
                    printf("In the first position on the second road, the license plate number is:% d The time of the car park is: \n", car.number);
                    scanf("%d", &car.arrive_time);
                    park[parktop] = car;
                    front++;
                    parktop++;
                }
                else
                {
                    printf("There is no vehicle on the road, and the parking lot is vacant! \n");
                }
            }
            break;

        default:
            printf("Error choose correct number in list");
            break;
        }
        if (choice == 3)
        {
            i = 0;
        }
    }
    return 0;
}
