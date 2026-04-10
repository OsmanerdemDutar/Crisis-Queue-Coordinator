#include "Team.h"

Team::Team()
    : teamID(-1),
      maxLoadCapacity(0),
      currentWorkload(0),
      missionStack(4) {
}

Team::Team(int id, int maxLoad)
    : teamID(id),
      maxLoadCapacity(maxLoad),
      currentWorkload(0),
      missionStack(4) {
}

int Team::getId() const {
    return teamID;
}

int Team::getMaxLoadCapacity() const {
    return maxLoadCapacity;
}

int Team::getCurrentWorkload() const {
    return currentWorkload;
}

void Team::setId(int id) {
    teamID = id;
}

void Team::setMaxLoadCapacity(int maxLoad) {
    maxLoadCapacity = maxLoad;
}

bool Team::hasActiveMission() const {
    return !missionStack.isEmpty();
}

bool Team::tryAssignRequest(const Request& req) {
    //Implement tryAssignRequest function as explained in the PDF.
    
    int newLoad = req.computeWorkloadContribution();
    if(newLoad + currentWorkload > maxLoadCapacity){
        return false;
    }
    currentWorkload += newLoad;
    missionStack.push(req);
    return true;
}

void Team::rollbackMission(RequestQueue& supplyQueue, RequestQueue& rescueQueue) {
    //Implement rollbackMission function as explained in the PDF.

    // Evacuate those waiting in the current queues to temporary queues.
    // (Because we have to return these things first)
    RequestQueue tempExistingSupply;
    RequestQueue tempExistingRescue;
    Request req;

    // Clear the supply queue
    while(supplyQueue.dequeue(req)) {
        tempExistingSupply.enqueue(req);
    }
    // Clear the rescue queue
    while(rescueQueue.dequeue(req)) {
        tempExistingRescue.enqueue(req);
    }

    // Add the returns in the stack (Task Cancellation) to empty queues.
    MissionStack tempStack;
    
    // Reverse the stack (LIFO -> FIFO preparation)
    int missionStackSize = missionStack.size();
    for(int i = 0; i < missionStackSize; i++){
        Request tempReq;
        missionStack.pop(tempReq);
        
        tempStack.push(tempReq);
        
    }

    // Add to the queues in sequential order. 
    // (Since the queues are currently empty, these will go to the very front)
    int tempStackSize = tempStack.size();
    for(int i = 0; i < tempStackSize; i++){
        Request tempReq;
        if(tempStack.pop(tempReq)){

            if( tempReq.getType() == "SUPPLY"){
                supplyQueue.enqueue(tempReq);
            }
            else if(tempReq.getType() == "RESCUE"){
                rescueQueue.enqueue(tempReq);
            }
        }
    }

    // Add the old ones to the back.
    while(tempExistingSupply.dequeue(req)) {
        supplyQueue.enqueue(req);
    }
    while(tempExistingRescue.dequeue(req)) {
        rescueQueue.enqueue(req);
    }
    
    currentWorkload = 0;
}

void Team::clearMission() {
    missionStack.clear();
    currentWorkload = 0;
}

const MissionStack& Team::getMissionStack() const {
    return missionStack;
}
