#include <stdio.h>

#define MAX_ROOMS 100

void initializeSystem(int lights[], int temps[], int motion[], int locks[], int rooms);
void displayMenu();
void controlLights(int lights[], int rooms);
void readTemperature(int temps[], int rooms);
void detectMotion(int motion[], int rooms);
void securitySystem(int locks[], int rooms);
void analyzeHouseStatus(int lights[], int temps[], int motion[], int locks[], int rooms);
void autoLock(int motion[], int locks[], int rooms, int *noMotionCount);
void tempAlert(int temps[], int rooms);
void energySavingSuggestion(int lights[], int rooms, int *lightUsageCount);

int main() {
    int lights[MAX_ROOMS];
    int temps[MAX_ROOMS];
    int motion[MAX_ROOMS];
    int locks[MAX_ROOMS];
    int rooms;
    int choice;
    int noMotionCount = 0;
    int lightUsageCount = 0;

    printf("Enter number of rooms: ");
    scanf("%d", &rooms);

    initializeSystem(lights, temps, motion, locks, rooms);

    while(1) {
        displayMenu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                controlLights(lights, rooms);
                lightUsageCount++;
                break;
            case 2:
                readTemperature(temps, rooms);
                break;
            case 3:
                detectMotion(motion, rooms);
                noMotionCount = 0;
                break;
            case 4:
                securitySystem(locks, rooms);
                break;
            case 5:
                analyzeHouseStatus(lights, temps, motion, locks, rooms);
                break;
            case 6:
                return 0;
            default:
                printf("Invalid choice\n");
        }
        noMotionCount++;
        autoLock(motion, locks, rooms, &noMotionCount);
        tempAlert(temps, rooms);
        energySavingSuggestion(lights, rooms, &lightUsageCount);
    }
}

void initializeSystem(int lights[], int temps[], int motion[], int locks[], int rooms) {
    for(int i=0; i<rooms; i++) {
        lights[i] = 0;
        temps[i] = 20 + (i % 5);
        motion[i] = 0;
        locks[i] = 1;
    }
}

void displayMenu() {
    printf("\n===== Smart Home Menu =====\n");
    printf("1. Toggle Light\n");
    printf("2. Read Temperature\n");
    printf("3. Check Motion Sensor\n");
    printf("4. Lock/Unlock Security System\n");
    printf("5. House Status Summary\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void controlLights(int lights[], int rooms) {
    int room;
    printf("Enter room number to toggle light (1-%d): ", rooms);
    scanf("%d", &room);
    if(room >=1 && room <= rooms) {
        lights[room-1] = !lights[room-1];
        printf("Light in Room %d is now %s.\n", room, lights[room-1] ? "ON" : "OFF");
    } else {
        printf("Invalid room number.\n");
    }
}

void readTemperature(int temps[], int rooms) {
    int room;
    printf("Enter room number to read temperature (1-%d): ", rooms);
    scanf("%d", &room);
    if(room >=1 && room <= rooms) {
        printf("Temperature in Room %d is %d°C.\n", room, temps[room-1]);
    } else {
        printf("Invalid room number.\n");
    }
}

void detectMotion(int motion[], int rooms) {
    int room;
    printf("Enter room number to check motion (1-%d): ", rooms);
    scanf("%d", &room);
    if(room >=1 && room <= rooms) {
        printf("Is there motion detected? (1-Yes / 0-No): ");
        scanf("%d", &motion[room-1]);
    } else {
        printf("Invalid room number.\n");
    }
}

void securitySystem(int locks[], int rooms) {
    int room;
    printf("Enter room number to toggle lock (1-%d): ", rooms);
    scanf("%d", &room);
    if(room >=1 && room <= rooms) {
        locks[room-1] = !locks[room-1];
        printf("Room %d is now %s.\n", room, locks[room-1] ? "Locked" : "Unlocked");
    } else {
        printf("Invalid room number.\n");
    }
}

void analyzeHouseStatus(int lights[], int temps[], int motion[], int locks[], int rooms) {
    for(int i=0; i<rooms; i++) {
        printf("Room %d: Light %s, Temp %d°C, %s, %s\n", i+1,
            lights[i] ? "ON" : "OFF",
            temps[i],
            motion[i] ? "Motion Detected" : "No Motion",
            locks[i] ? "Locked" : "Unlocked");
    }
}

void autoLock(int motion[], int locks[], int rooms, int *noMotionCount) {
    if(*noMotionCount >= 5) {
        for(int i=0; i<rooms; i++) {
            if(!motion[i]) {
                locks[i] = 1;
            }
        }
        *noMotionCount = 0;
        printf("Auto-Lock Activated: All doors locked due to no motion.\n");
    }
}

void tempAlert(int temps[], int rooms) {
    for(int i=0; i<rooms; i++) {
        if(temps[i] > 30) {
            printf("Warning: Room %d temperature is high (%d°C)!\n", i+1, temps[i]);
        }
    }
}

void energySavingSuggestion(int lights[], int rooms, int *lightUsageCount) {
    if(*lightUsageCount >= 5) {
        int allOn = 1;
        for(int i=0; i<rooms; i++) {
            if(!lights[i]) {
                allOn = 0;
                break;
            }
        }
        if(allOn) {
            printf("Energy Saving Suggestion: Consider turning off lights to save energy.\n");
            *lightUsageCount = 0;
        }
    }
}
