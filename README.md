# Crisis Queue Coordinator

A C++11 emergency coordination simulator that manages supply and rescue requests with dynamic circular queues, mission stacks, team capacity control, and rollback-safe dispatch logic.

---

## Overview

Crisis Queue Coordinator is a queue-and-stack based emergency response simulation.  
The system keeps two request queues:

- SUPPLY
- RESCUE

Teams are assigned the most urgent request by comparing the front of both queues.  
Each team stores its active mission in a stack, and if capacity is exceeded, the mission is rolled back safely.

---

## Core Features

- Dynamic circular queues for supply and rescue requests
- Dynamic mission stack for each team
- Emergency score based request selection
- Team capacity management
- Rollback on overload
- Command-based simulation flow
- File input support with stdout output

---

## Emergency Priority

The system compares the front request of both queues.

### Supply score
```text
emergencyLevel * 10 + min(amount, 50)
```

### Rescue score
```text
emergencyLevel * 10 + numPeople * riskMultiplier
```

Risk multipliers:

- LOW = 1
- MEDIUM = 2
- HIGH = 3

If scores are equal, RESCUE has priority.

---

## Workload Rules

- SUPPLY workload = `amount`
- RESCUE workload = `numPeople * riskMultiplier`

If a team exceeds its maximum load during mission assignment:

- the mission is cancelled,
- assigned requests are returned to their original queues,
- the team stack is cleared.

---

## Supported Commands

```text
INIT_TEAMS <numTeams>
SET_TEAM_CAPACITY <teamID> <maxLoadCapacity>
ADD_SUPPLY <id> <city> <supplyType> <amount> <emergencyLevel>
ADD_RESCUE <id> <city> <numPeople> <buildingRisk> <emergencyLevel>
REMOVE_REQUEST <id>
HANDLE_EMERGENCY <teamID> <k>
DISPATCH_TEAM <teamID>
PRINT_QUEUES
PRINT_TEAM <teamID>
CLEAR
```

---

## Build

```bash
g++ -std=c++11 *.cpp *.h -o QuakeAssist
```

Run with an input file:

```bash
./QuakeAssist example_input.txt
```

---

## Project Structure

```text
main.cpp
Request.cpp / Request.h
RequestQueue.cpp / RequestQueue.h
MissionStack.cpp / MissionStack.h
Team.cpp / Team.h
QuakeAssistController.cpp / QuakeAssistController.h
```

---

## Example Use

```text
INIT_TEAMS 2
SET_TEAM_CAPACITY 0 80
SET_TEAM_CAPACITY 1 120
ADD_SUPPLY S101 ANKARA WATER 40 4
ADD_RESCUE R205 IZMIR 7 HIGH 5
HANDLE_EMERGENCY 1 2
DISPATCH_TEAM 1
PRINT_QUEUES
```
