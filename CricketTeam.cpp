#include <string>
#include <iostream>
#include "CricketTeam.h"

//constructor intializes head and nullptr
CricketTeam::CricketTeam(): head(nullptr), tail(nullptr){}

bool CricketTeam::noTeam() const
{
    //check if no head or tail Cricketer
    if(head == nullptr && tail == nullptr)
    {
        return true;
    }
    return false;
}

CricketTeam::~CricketTeam()
{
    Cricketer *p;
	while (head != nullptr) {
		p = head;
		head = head->next;
		delete p;
	}
    head = nullptr;
    tail = nullptr;
}


CricketTeam::CricketTeam(const CricketTeam& rhs)
{   
    // checks if no Cricketers then assigns Cricketers
    if (rhs.head == nullptr) {
        head = nullptr;
        tail = nullptr;
    } else {
        // declares and initializes the first Cricketer
        head = new Cricketer;
        head->value = rhs.head->value;
        head->first = rhs.head->first;
        head->last = rhs.head->last;
        head->previous = nullptr;
        head->next = nullptr; 

        // save for previous pointer
        Cricketer *currentNew = head;
        Cricketer *current = rhs.head->next;

        // loops and copies
        while (current != nullptr) {
            // creates new Cricketer and initializes values
            Cricketer *newCricketer = new Cricketer;
            newCricketer->value = current->value;
            newCricketer->first = current->first;
            newCricketer->last = current->last;
            newCricketer->previous = currentNew;
            
            // makes sure next value is null
            newCricketer->next = nullptr;

            // gives currentNew's next pointer the value of newCricketer
            currentNew->next = newCricketer;
            
            // loops one ahead
            currentNew = newCricketer;
            current = current->next;
        }
        // assigns the tail pointer
        tail = currentNew;
    }
}

// Swap function implementation
void CricketTeam::swap(CricketTeam& other)
{
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

const CricketTeam& CricketTeam::operator=(const CricketTeam& rhs)
{   
    // Check if it's the same object (self-assignment check)
    if (this == &rhs) {
        return *this;
    }

    // Create a temporary copy of rhs
    CricketTeam temp(rhs);

    // Swap the contents with the temporary copy
    swap(temp);

    return *this;
}

int CricketTeam::cricketerCount() const
{
    //easier vairable to see
    Cricketer* current = head;
    int count = 0;

    //traverse through list
    while(current != nullptr)
    {
        current = current->next;
        count++;
    }
    return count;
}

bool CricketTeam::addCricketer(const std::string& firstName, const std::string& lastName, const CricketType& value) {
    // If the cricketer is already on the team, return false
    if (rosteredOnCricketTeam(firstName, lastName)) {
        return false;
    }

    // Create a new Cricketer with the cricketer's details
    Cricketer* newCricketer = new Cricketer;
    newCricketer->first = firstName;
    newCricketer->last = lastName;
    newCricketer->value = value;
    newCricketer->next = nullptr;
    newCricketer->previous = nullptr;

    // If the list is empty, initialize head and tail
    if (head == nullptr && tail == nullptr) {
        head = newCricketer;
        tail = newCricketer;
        return true;
    }

    Cricketer* temp = head;

    // Traverse the list to find the correct insertion point
    while (temp != nullptr) {
        if ((newCricketer->last < temp->last) || (newCricketer->last == temp->last && newCricketer->first < temp->first)) {
            // Insert newCricketer before temp
            newCricketer->next = temp;
            newCricketer->previous = temp->previous;

            if (temp->previous != nullptr) {
                temp->previous->next = newCricketer;
            } else {
                head = newCricketer; // Update head if newCricketer is inserted at the beginning
            }

            temp->previous = newCricketer;
            return true;
        }

        if (temp->next == nullptr) {
            // If temp is the last Cricketer, insert newCricketer after temp
            temp->next = newCricketer;
            newCricketer->previous = temp;
            tail = newCricketer;
            return true;
        }

        temp = temp->next;
    }

    return true;
}


bool CricketTeam::substituteCricketer(const std::string& firstName, const std::string& lastName, const CricketType & value)
{
    //if no Cricketers
    if(head == nullptr && tail == nullptr)
    {
        return false;
    }

    //traver list

    //variable for current Cricketer
    Cricketer* current = head;

    //traverase through list
    while(current != nullptr)
    {   
        //check if same
        if(current->first == firstName && current->last == lastName)
        {
            //change value
            current->value = value;
            return true;
        }
        current = current->next;
    }

    return false;
}

bool CricketTeam::addOrSubstitute(const std::string& firstName, const std::string& lastName, const CricketType& value)
{
    // If no Cricketers in the list, initialize the list with the new Cricketer
    if (head == nullptr && tail == nullptr)
    {
        head = new Cricketer;
        head->first = firstName;
        head->last = lastName;
        head->value = value;
        head->previous = nullptr;
        head->next = nullptr;
        tail = head;
        return true;
    }

    // Define variable to traverse the list
    Cricketer* current = head;

    // Traverse the list to see if Cricketer exists and update the value if found
    while (current != nullptr)
    {
        if (current->first == firstName && current->last == lastName)
        {
            current->value = value; // Update value if Cricketer is found
            return true; // Always return true
        }
        current = current->next;
    }
    
    // If Cricketer is not found, add a new Cricketer using the addCricketer method
    addCricketer(firstName, lastName, value);

    return true; // Always return true
}

bool CricketTeam::releaseCricketer(const std::string& firstName, const std::string& lastName)
{   
    //if no Cricketers
    if(head == nullptr && tail == nullptr)
    {
        return false;
    }

    //traverse through list

    //easier variable to see current Cricketer
    Cricketer* current = head;

    while(current != nullptr)
    {

        if(current->first == firstName && current->last == lastName)
        {
            //only one Cricketer
            if(current == head && current == tail)
            {
                delete current;
                head = nullptr;
                tail = nullptr;
            }
            //if the Cricketer is in front 
            else if(head == current)
            {
                head = head->next;
                head->previous = nullptr;
                delete current;
            }
            //if Cricketer is in the back
            else if(tail == current)
            {
                tail = tail->previous;
                tail->next = nullptr;
                delete current;
            }
            //in the middle
            else
            {
                //save values
                Cricketer* before = current->previous;
                Cricketer* after = current->next;
                //give them values
                before->next = after;
                after->previous = before;

                delete current;
            }
            return true;
        }
        current = current->next;
    }
    return false;
}

bool CricketTeam::rosteredOnCricketTeam(const std::string& firstName, const std::string& lastName) const
{
    //if no Cricketers
    if(head == nullptr && tail == nullptr)
    {
        return false;
    }

    //find if in the team
    
    //vairable to traverse
    Cricketer* current = head;

    while(current != nullptr)
    {
        if(current->first == firstName && current->last == lastName)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool CricketTeam::searchForCricketer(const std::string& firstName, const std::string& lastName, CricketType& value) const
{
    //if no Cricketers
    if(head == nullptr && tail == nullptr)
    {
        return false;
    }

    //traverse through list

    //variable to traverse
    Cricketer* current  = head;

    while(current != nullptr)
    {
        if(current->first == firstName && current->last == lastName)
        {
            //sets value equal to the value in the list
            value = current->value;
            return true;
        }
        current = current->next;
    }
    return false;
}

//check if I can use cricketerCount function
bool CricketTeam::checkTeamForCricketer(int i, std::string& firstName, std::string& lastName, CricketType& value) const
{   
    //check if no Cricketers
    if(tail == nullptr && head == nullptr)
    {
        return false;
    }

    // Check if the index is within bounds
    if (i < 0 || i >= cricketerCount())
    {
        return false;
    }

    // Traverse through the list
    Cricketer* current = head;

    for (int index = 0; index < i && current != nullptr; ++index)
    {
        current = current->next;
    }

    // If current is not nullptr, copy the data
    if (current != nullptr)
    {
        firstName = current->first;
        lastName = current->last;
        value = current->value;
        return true;
    }

    return false;
}

void CricketTeam::tradeCricketTeams(CricketTeam& other)
{
    //save both head and tail variables
    Cricketer* temp_h = head;
    Cricketer* temp_t = tail;
    //swap both variables
    head = other.head;
    other.head = temp_h;
    tail = other.tail;
    other.tail = temp_t;
}

bool mergeCricketers(const CricketTeam & odOne, const CricketTeam & odTwo, CricketTeam & odJoined)
{
    bool isConsistent = true;
    CricketType valueOne, valueTwo;
    std::string first, last;

    CricketTeam tempTeam;

    //add list from odOne into joined without with values same in both
    for(int i = 0; i < odOne.cricketerCount();i++)
    {
        //retrieves values
        if(odOne.checkTeamForCricketer(i, first, last, valueOne))
        //searches all of list two to see if those values are in it
            if (odTwo.searchForCricketer(first, last, valueTwo))
            //compares for concistency in value vairable of both lists
                if(valueOne == valueTwo)
                    {
                        tempTeam.addOrSubstitute(first,last,valueOne);
                    }
                else
                {
                    isConsistent = false;
                }
        else
        {
            tempTeam.addOrSubstitute(first,last,valueOne);
        }
    }

    //add values in second list
    for(int i = 0; i < odTwo.cricketerCount();i++)
    {
        //retrieves values of every cricket
        if(odTwo.checkTeamForCricketer(i, first, last, valueTwo)) 
        {
            //makes sure that is not the same as list one
            if(!odOne.searchForCricketer(first, last, valueOne)) 
                {
                    //adds cricket
                    tempTeam.addOrSubstitute(first, last, valueTwo);
                }
        }
    }
    //delete existing memory in odJoined
    for(int i = 0; i < odJoined.cricketerCount();i++)
        {
            //retrieves values
            if(odJoined.checkTeamForCricketer(i, first, last, valueOne))
            {
                //deletes Cricketer
                odJoined.releaseCricketer(first, last);
            }
        }
    // Copy cricketers from tempTeam to odJoined
    for (int i = 0; i < tempTeam.cricketerCount(); i++) 
        {
            if (tempTeam.checkTeamForCricketer(i, first, last, valueOne)) {
                odJoined.addOrSubstitute(first, last, valueOne);
            }
        }
    return isConsistent;
}

void checkCricketers (const std::string& fsearch, const std::string& lsearch, const CricketTeam& odOne, CricketTeam& odResult)
{   
    //declaration of variables to hold values
    CricketType value;
    std::string first, last;

    CricketTeam tempTeam;

     // Traverse through odOne and add matching cricketers to tempTeam
    for(int i = 0; i < odOne.cricketerCount(); i++) {
        if(odOne.checkTeamForCricketer(i, first, last, value)) {
            // Check if the value matches the search criteria
            if ((first == fsearch || fsearch == "*") && (last == lsearch || lsearch == "*")) {
                tempTeam.addOrSubstitute(first, last, value);
            }
        }
    }

    //make sure oddResult has its memory deallocated
    for(int i = 0; i < odResult.cricketerCount();i++)
    {
        if(odResult.checkTeamForCricketer(i,first, last, value))
            {
                odResult.releaseCricketer(first,last);
            }
    }

    //make sure memory is not delallocated if the same array 
    for(int i = 0; i < tempTeam.cricketerCount(); i++) {
        if(tempTeam.checkTeamForCricketer(i, first, last, value)) {
            odResult.addOrSubstitute(first, last, value);
        }
    }
}