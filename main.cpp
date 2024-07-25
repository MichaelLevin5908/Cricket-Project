#include <iostream>
#include <cassert>
#include "CricketTeam.h"

void runTests() {
    CricketTeam sriLankaCricket;
    std::string firstName, lastName;
    CricketType value;

    // Default constructor and initial state
    assert(sriLankaCricket.cricketerCount() == 0); // Test size
    assert(sriLankaCricket.noTeam()); // Test empty
    assert(!sriLankaCricket.releaseCricketer("Wanindu", "Hasaranga")); // Nothing to erase

    // Add a single cricketer
    assert(sriLankaCricket.addCricketer("Wanindu", "Hasaranga", 1)); // Add one cricketer
    assert(sriLankaCricket.cricketerCount() == 1); // Size should be 1
    assert(!sriLankaCricket.noTeam()); // Should not be empty
    assert(sriLankaCricket.rosteredOnCricketTeam("Wanindu", "Hasaranga")); // Cricketer is in the team
    assert(!sriLankaCricket.rosteredOnCricketTeam("Angelo", "Mathews")); // Cricketer is not in the team

    // Add duplicate cricketer
    assert(!sriLankaCricket.addCricketer("Wanindu", "Hasaranga", 1)); // Should not add duplicate
    assert(sriLankaCricket.cricketerCount() == 1); // Size should remain 1

    // Substitute cricketer's value
    assert(sriLankaCricket.substituteCricketer("Wanindu", "Hasaranga", 2)); // Substitute value
    assert(sriLankaCricket.searchForCricketer("Wanindu", "Hasaranga", value));
    assert(value == 2); // Value should be updated

    // Add or substitute (substitute case)
    assert(sriLankaCricket.addOrSubstitute("Wanindu", "Hasaranga", 3));
    assert(sriLankaCricket.searchForCricketer("Wanindu", "Hasaranga", value));
    assert(value == 3); // Value should be updated again

    // Add or substitute (add case)
    assert(sriLankaCricket.addOrSubstitute("Angelo", "Mathews", 4));
    assert(sriLankaCricket.cricketerCount() == 2); // Size should be 2 now
    assert(sriLankaCricket.searchForCricketer("Angelo", "Mathews", value));
    assert(value == 4); // Angelo Mathews should be added with value 4

    // Release cricketer
    assert(sriLankaCricket.releaseCricketer("Wanindu", "Hasaranga"));
    assert(sriLankaCricket.cricketerCount() == 1); // Size should be 1
    assert(!sriLankaCricket.rosteredOnCricketTeam("Wanindu", "Hasaranga")); // Wanindu should be removed

    // Add multiple cricketers
    assert(sriLankaCricket.addCricketer("Kusal", "Perera", 5));
    assert(sriLankaCricket.addCricketer("Dimuth", "Karunaratne", 6));
    assert(sriLankaCricket.addCricketer("Dinesh", "Chandimal", 7));
    assert(sriLankaCricket.cricketerCount() == 4); // Size should be 4

    // Check sorted order
    assert(sriLankaCricket.checkTeamForCricketer(0, firstName, lastName, value));
    assert(firstName == "Dinesh" && lastName == "Chandimal");
    assert(sriLankaCricket.checkTeamForCricketer(1, firstName, lastName, value));
    assert(firstName == "Dimuth" && lastName == "Karunaratne");
    assert(sriLankaCricket.checkTeamForCricketer(2, firstName, lastName, value));
    assert(firstName == "Angelo" && lastName == "Mathews");
    assert(sriLankaCricket.checkTeamForCricketer(3, firstName, lastName, value));
    assert(firstName == "Kusal" && lastName == "Perera");

    // Test edge cases for release
    assert(!sriLankaCricket.releaseCricketer("Non", "Existent"));
    assert(sriLankaCricket.releaseCricketer("Dimuth", "Karunaratne"));
    assert(sriLankaCricket.cricketerCount() == 3);
    assert(!sriLankaCricket.rosteredOnCricketTeam("Dimuth", "Karunaratne"));

    // Test empty after all releases
    assert(sriLankaCricket.releaseCricketer("Kusal", "Perera"));
    assert(sriLankaCricket.releaseCricketer("Angelo", "Mathews"));
    assert(sriLankaCricket.releaseCricketer("Dinesh", "Chandimal"));
    assert(sriLankaCricket.cricketerCount() == 0);
    assert(sriLankaCricket.noTeam());

    // Test copy constructor
    sriLankaCricket.addCricketer("Lasith", "Malinga", 99);
    CricketTeam sriLankaCricketCopy(sriLankaCricket);
    assert(sriLankaCricketCopy.cricketerCount() == 1);
    assert(sriLankaCricketCopy.rosteredOnCricketTeam("Lasith", "Malinga"));

    // Test assignment operator
    CricketTeam sriLankaCricketAssign;
    sriLankaCricketAssign = sriLankaCricket;
    assert(sriLankaCricketAssign.cricketerCount() == 1);
    assert(sriLankaCricketAssign.rosteredOnCricketTeam("Lasith", "Malinga"));

    // Add more cricketers to original and check copy is unaffected
    sriLankaCricket.addCricketer("Kumar", "Sangakkara", 11);
    assert(sriLankaCricket.cricketerCount() == 2);
    assert(sriLankaCricketCopy.cricketerCount() == 1);

    // Test trade teams
    CricketTeam indiaCricket;
    indiaCricket.addCricketer("Virat", "Kohli", 18);
    indiaCricket.addCricketer("Rohit", "Sharma", 45);
    indiaCricket.addCricketer("Jasprit", "Bumrah", 93);

    sriLankaCricket.tradeCricketTeams(indiaCricket);
    assert(sriLankaCricket.cricketerCount() == 3);
    assert(indiaCricket.cricketerCount() == 2);
    assert(sriLankaCricket.rosteredOnCricketTeam("Virat", "Kohli"));
    assert(indiaCricket.rosteredOnCricketTeam("Kumar", "Sangakkara"));

    // Test search function
    assert(sriLankaCricket.searchForCricketer("Virat", "Kohli", value));
    assert(value == 18);

    // Test bounds checking for checkTeamForCricketer
    assert(!sriLankaCricket.checkTeamForCricketer(-1, firstName, lastName, value)); // Out of bounds
    assert(!sriLankaCricket.checkTeamForCricketer(3, firstName, lastName, value)); // Out of bounds

    // Additional edge cases
    CricketTeam emptyTeam;
    CricketTeam fullTeam;
    for (int i = 0; i < 100; ++i) {
        fullTeam.addCricketer("First" + std::to_string(i), "Last" + std::to_string(i), i);
    }
    assert(fullTeam.cricketerCount() == 100);

    for (int i = 0; i < 100; ++i) {
        assert(fullTeam.releaseCricketer("First" + std::to_string(i), "Last" + std::to_string(i)));
    }
    assert(fullTeam.cricketerCount() == 0);

    // Test edge cases for addCricketer in sorted order
    CricketTeam sortedTeam;
    assert(sortedTeam.addCricketer("Z", "Last", 1));
    assert(sortedTeam.addCricketer("A", "Last", 2));
    assert(sortedTeam.addCricketer("M", "Last", 3));
    assert(sortedTeam.checkTeamForCricketer(0, firstName, lastName, value));
    assert(firstName == "A" && lastName == "Last");
    assert(sortedTeam.checkTeamForCricketer(1, firstName, lastName, value));
    assert(firstName == "M" && lastName == "Last");
    assert(sortedTeam.checkTeamForCricketer(2, firstName, lastName, value));
    assert(firstName == "Z" && lastName == "Last");

    // Test edge cases for addOrSubstitute
    CricketTeam addOrSubTeam;
    assert(addOrSubTeam.addOrSubstitute("X", "Player", 10)); // Add new
    assert(addOrSubTeam.addOrSubstitute("X", "Player", 20)); // Substitute existing
    assert(addOrSubTeam.searchForCricketer("X", "Player", value));
    assert(value == 20);

    // Test edge cases for substituteCricketer
    CricketTeam substituteTeam;
    assert(!substituteTeam.substituteCricketer("Non", "Existent", 100)); // Substitute non-existent
    assert(substituteTeam.addCricketer("Exist", "Ent", 50)); // Add cricketer
    assert(substituteTeam.substituteCricketer("Exist", "Ent", 60)); // Substitute existing
    assert(substituteTeam.searchForCricketer("Exist", "Ent", value));
    assert(value == 60);

    // Test more edge cases for releaseCricketer
    CricketTeam releaseTeam;
    assert(!releaseTeam.releaseCricketer("Non", "Existent")); // Release non-existent
    assert(releaseTeam.addCricketer("Only", "Player", 1)); // Add cricketer
    assert(releaseTeam.releaseCricketer("Only", "Player")); // Release existing
    assert(releaseTeam.cricketerCount() == 0);
    assert(releaseTeam.noTeam());

    // Add, substitute, and release in different orders
    CricketTeam mixedTeam;
    assert(mixedTeam.addCricketer("A", "First", 1));
    assert(mixedTeam.addCricketer("B", "Second", 2));
    assert(mixedTeam.addOrSubstitute("A", "First", 3)); // Substitute existing
    assert(mixedTeam.addOrSubstitute("C", "Third", 4)); // Add new
    assert(mixedTeam.releaseCricketer("B", "Second")); // Release existing
    assert(mixedTeam.cricketerCount() == 2);
    assert(mixedTeam.searchForCricketer("A", "First", value));
    assert(value == 3);
    assert(mixedTeam.searchForCricketer("C", "Third", value));
    assert(value == 4);

    // Test edge case for adding cricketers with the same last name
    CricketTeam sameLastNameTeam;
    assert(sameLastNameTeam.addCricketer("A", "Smith", 1));
    assert(sameLastNameTeam.addCricketer("B", "Smith", 2));
    assert(sameLastNameTeam.addCricketer("C", "Smith", 3));
    assert(sameLastNameTeam.cricketerCount() == 3);
    assert(sameLastNameTeam.checkTeamForCricketer(0, firstName, lastName, value));
    assert(firstName == "A" && lastName == "Smith");
    assert(sameLastNameTeam.checkTeamForCricketer(1, firstName, lastName, value));
    assert(firstName == "B" && lastName == "Smith");
    assert(sameLastNameTeam.checkTeamForCricketer(2, firstName, lastName, value));
    assert(firstName == "C" && lastName == "Smith");

    // Test edge case for adding cricketers with the same first name
    CricketTeam sameFirstNameTeam;
    assert(sameFirstNameTeam.addCricketer("John", "Doe1", 1));
    assert(sameFirstNameTeam.addCricketer("John", "Doe2", 2));
    assert(sameFirstNameTeam.addCricketer("John", "Doe3", 3));
    assert(sameFirstNameTeam.cricketerCount() == 3);
    assert(sameFirstNameTeam.checkTeamForCricketer(0, firstName, lastName, value));
    assert(firstName == "John" && lastName == "Doe1");
    assert(sameFirstNameTeam.checkTeamForCricketer(1, firstName, lastName, value));
    assert(firstName == "John" && lastName == "Doe2");
    assert(sameFirstNameTeam.checkTeamForCricketer(2, firstName, lastName, value));
    assert(firstName == "John" && lastName == "Doe3");

    // Test releasing cricketers with the same first or last name
    assert(sameLastNameTeam.releaseCricketer("B", "Smith"));
    assert(sameLastNameTeam.cricketerCount() == 2);
    assert(!sameLastNameTeam.rosteredOnCricketTeam("B", "Smith"));

    assert(sameFirstNameTeam.releaseCricketer("John", "Doe2"));
    assert(sameFirstNameTeam.cricketerCount() == 2);
    assert(!sameFirstNameTeam.rosteredOnCricketTeam("John", "Doe2"));

    // Test constructor with another team
    CricketTeam constructorTestTeam(sameFirstNameTeam);
    assert(constructorTestTeam.cricketerCount() == 2);
    assert(constructorTestTeam.rosteredOnCricketTeam("John", "Doe1"));
    assert(constructorTestTeam.rosteredOnCricketTeam("John", "Doe3"));

    // Test assignment operator with another team
    CricketTeam assignmentTestTeam;
    assignmentTestTeam = sameLastNameTeam;
    assert(assignmentTestTeam.cricketerCount() == 2);
    assert(assignmentTestTeam.rosteredOnCricketTeam("A", "Smith"));
    assert(assignmentTestTeam.rosteredOnCricketTeam("C", "Smith"));

    // Test edge case for assignment operator with self-assignment
    CricketTeam selfAssignTeam;
    selfAssignTeam.addCricketer("Self", "Assign", 1);
    selfAssignTeam = selfAssignTeam; // Self-assignment
    assert(selfAssignTeam.cricketerCount() == 1);
    assert(selfAssignTeam.rosteredOnCricketTeam("Self", "Assign"));

    // Test adding and releasing a large number of cricketers
    CricketTeam largeTeam;
    for (int i = 0; i < 1000; ++i) {
        assert(largeTeam.addCricketer("First" + std::to_string(i), "Last" + std::to_string(i), i));
    }
    assert(largeTeam.cricketerCount() == 1000);

    for (int i = 0; i < 1000; ++i) {
        assert(largeTeam.releaseCricketer("First" + std::to_string(i), "Last" + std::to_string(i)));
    }
    assert(largeTeam.cricketerCount() == 0);
    assert(largeTeam.noTeam());

    // Test edge case for releasing from an empty team
    CricketTeam emptyReleaseTeam;
    assert(!emptyReleaseTeam.releaseCricketer("Non", "Existent")); // Release from empty team should return false

    // Test edge case for substituting in an empty team
    CricketTeam emptySubstituteTeam;
    assert(!emptySubstituteTeam.substituteCricketer("Non", "Existent", 100)); // Substitute in empty team should return false

    // Test edge case for adding duplicate cricketers
    CricketTeam duplicateTestTeam;
    assert(duplicateTestTeam.addCricketer("Duplicate", "Cricketer", 1));
    assert(!duplicateTestTeam.addCricketer("Duplicate", "Cricketer", 2)); // Adding duplicate should return false

    // Test edge case for releasing and adding the same cricketer
    CricketTeam releaseAddTestTeam;
    assert(releaseAddTestTeam.addCricketer("Release", "Add", 1));
    assert(releaseAddTestTeam.releaseCricketer("Release", "Add"));
    assert(releaseAddTestTeam.addCricketer("Release", "Add", 2));
    assert(releaseAddTestTeam.cricketerCount() == 1);
    assert(releaseAddTestTeam.searchForCricketer("Release", "Add", value));
    assert(value == 2);

    // Test edge case for releasing all cricketers
    CricketTeam releaseAllTeam;
    for (int i = 0; i < 10; ++i) {
        assert(releaseAllTeam.addCricketer("First" + std::to_string(i), "Last" + std::to_string(i), i));
    }
    for (int i = 0; i < 10; ++i) {
        assert(releaseAllTeam.releaseCricketer("First" + std::to_string(i), "Last" + std::to_string(i)));
    }
    assert(releaseAllTeam.cricketerCount() == 0);
    assert(releaseAllTeam.noTeam());

    // Test edge case for substituting all cricketers
    CricketType newValue = 99;
    CricketTeam substituteAllTeam;
    for (int i = 0; i < 10; ++i) {
        assert(substituteAllTeam.addCricketer("First" + std::to_string(i), "Last" + std::to_string(i), i));
    }
    for (int i = 0; i < 10; ++i) {
        assert(substituteAllTeam.substituteCricketer("First" + std::to_string(i), "Last" + std::to_string(i), newValue));
    }
    for (int i = 0; i < 10; ++i) {
        assert(substituteAllTeam.searchForCricketer("First" + std::to_string(i), "Last" + std::to_string(i), value));
        assert(value == newValue);
    }

    // Test edge case for trading teams when both teams are empty
    CricketTeam emptyTeam1, emptyTeam2;
    emptyTeam1.tradeCricketTeams(emptyTeam2);
    assert(emptyTeam1.noTeam());
    assert(emptyTeam2.noTeam());

    // Test edge case for trading teams when one team is empty
    CricketTeam tradeTeam1, tradeTeam2;
    assert(tradeTeam1.addCricketer("Trade", "One", 1));
    tradeTeam1.tradeCricketTeams(tradeTeam2);
    assert(tradeTeam1.noTeam());
    assert(tradeTeam2.cricketerCount() == 1);
    assert(tradeTeam2.rosteredOnCricketTeam("Trade", "One"));

    // Test edge case for trading teams when both teams have cricketers
    CricketTeam tradeTeam3, tradeTeam4;
    assert(tradeTeam3.addCricketer("Team3", "Player1", 1));
    assert(tradeTeam3.addCricketer("Team3", "Player2", 2));
    assert(tradeTeam4.addCricketer("Team4", "Player1", 3));
    tradeTeam3.tradeCricketTeams(tradeTeam4);
    assert(tradeTeam3.cricketerCount() == 1);
    assert(tradeTeam4.cricketerCount() == 2);
    assert(tradeTeam3.rosteredOnCricketTeam("Team4", "Player1"));
    assert(tradeTeam4.rosteredOnCricketTeam("Team3", "Player1"));
    assert(tradeTeam4.rosteredOnCricketTeam("Team3", "Player2"));

    // Test edge case for trading teams with different sizes
    CricketTeam tradeTeam5, tradeTeam6;
    assert(tradeTeam5.addCricketer("Team5", "Player1", 1));
    assert(tradeTeam5.addCricketer("Team5", "Player2", 2));
    assert(tradeTeam6.addCricketer("Team6", "Player1", 3));
    assert(tradeTeam6.addCricketer("Team6", "Player2", 4));
    assert(tradeTeam6.addCricketer("Team6", "Player3", 5));
    tradeTeam5.tradeCricketTeams(tradeTeam6);
    assert(tradeTeam5.cricketerCount() == 3);
    assert(tradeTeam6.cricketerCount() == 2);
    assert(tradeTeam5.rosteredOnCricketTeam("Team6", "Player1"));
    assert(tradeTeam5.rosteredOnCricketTeam("Team6", "Player2"));
    assert(tradeTeam5.rosteredOnCricketTeam("Team6", "Player3"));
    assert(tradeTeam6.rosteredOnCricketTeam("Team5", "Player1"));
    assert(tradeTeam6.rosteredOnCricketTeam("Team5", "Player2"));

    // Test edge case for trading teams with one team having multiple cricketers
    CricketTeam tradeTeam7, tradeTeam8;
    for (int i = 0; i < 5; ++i) {
        assert(tradeTeam7.addCricketer("Team7", "Player" + std::to_string(i), i));
    }
    assert(tradeTeam8.addCricketer("Team8", "Player1", 1));
    tradeTeam7.tradeCricketTeams(tradeTeam8);
    assert(tradeTeam7.cricketerCount() == 1);
    assert(tradeTeam8.cricketerCount() == 5);
    assert(tradeTeam7.rosteredOnCricketTeam("Team8", "Player1"));
    for (int i = 0; i < 5; ++i) {
        assert(tradeTeam8.rosteredOnCricketTeam("Team7", "Player" + std::to_string(i)));
    }

    // Test edge case for searching in an empty team
    CricketTeam searchEmptyTeam;
    assert(!searchEmptyTeam.searchForCricketer("Non", "Existent", value));

    // Test edge case for adding and then releasing a cricketer
    CricketTeam addReleaseTeam;
    assert(addReleaseTeam.addCricketer("Add", "Release", 1));
    assert(addReleaseTeam.releaseCricketer("Add", "Release"));
    assert(addReleaseTeam.cricketerCount() == 0);
    assert(addReleaseTeam.noTeam());

    // Test edge case for substituting and then releasing a cricketer
    CricketTeam subReleaseTeam;
    assert(subReleaseTeam.addCricketer("Sub", "Release", 1));
    assert(subReleaseTeam.substituteCricketer("Sub", "Release", 2));
    assert(subReleaseTeam.releaseCricketer("Sub", "Release"));
    assert(subReleaseTeam.cricketerCount() == 0);
    assert(subReleaseTeam.noTeam());

    // Test edge case for substituting a non-existent cricketer
    CricketTeam nonExistSubTeam;
    assert(!nonExistSubTeam.substituteCricketer("Non", "Existent", 1));

    // Test edge case for adding cricketers with special characters
    CricketTeam specialCharTeam;
    assert(specialCharTeam.addCricketer("First@", "Last#", 1));
    assert(specialCharTeam.addCricketer("First$", "Last%", 2));
    assert(specialCharTeam.cricketerCount() == 2);
    assert(specialCharTeam.rosteredOnCricketTeam("First@", "Last#"));
    assert(specialCharTeam.rosteredOnCricketTeam("First$", "Last%"));

    // Test edge case for releasing cricketers with special characters
    assert(specialCharTeam.releaseCricketer("First@", "Last#"));
    assert(specialCharTeam.cricketerCount() == 1);
    assert(!specialCharTeam.rosteredOnCricketTeam("First@", "Last#"));

    // Test edge case for substituting cricketers with special characters
    assert(specialCharTeam.substituteCricketer("First$", "Last%", 3));
    assert(specialCharTeam.searchForCricketer("First$", "Last%", value));
    assert(value == 3);

    // Test edge case for releasing all cricketers with special characters
    assert(specialCharTeam.releaseCricketer("First$", "Last%"));
    assert(specialCharTeam.cricketerCount() == 0);
    assert(specialCharTeam.noTeam());

    // Test edge case for adding cricketers with numerical names
    CricketTeam numericalNameTeam;
    assert(numericalNameTeam.addCricketer("First1", "Last1", 1));
    assert(numericalNameTeam.addCricketer("First2", "Last2", 2));
    assert(numericalNameTeam.cricketerCount() == 2);
    assert(numericalNameTeam.rosteredOnCricketTeam("First1", "Last1"));
    assert(numericalNameTeam.rosteredOnCricketTeam("First2", "Last2"));

    // Test edge case for releasing cricketers with numerical names
    assert(numericalNameTeam.releaseCricketer("First1", "Last1"));
    assert(numericalNameTeam.cricketerCount() == 1);
    assert(!numericalNameTeam.rosteredOnCricketTeam("First1", "Last1"));

    // Test edge case for substituting cricketers with numerical names
    assert(numericalNameTeam.substituteCricketer("First2", "Last2", 3));
    assert(numericalNameTeam.searchForCricketer("First2", "Last2", value));
    assert(value == 3);

    // Test edge case for releasing all cricketers with numerical names
    assert(numericalNameTeam.releaseCricketer("First2", "Last2"));
    assert(numericalNameTeam.cricketerCount() == 0);
    assert(numericalNameTeam.noTeam());

    // Test edge case for adding cricketers with mixed case names
    CricketTeam mixedCaseTeam;
    assert(mixedCaseTeam.addCricketer("First", "LAST", 1));
    assert(mixedCaseTeam.addCricketer("first", "last", 2));
    assert(mixedCaseTeam.cricketerCount() == 2);
    assert(mixedCaseTeam.rosteredOnCricketTeam("First", "LAST"));
    assert(mixedCaseTeam.rosteredOnCricketTeam("first", "last"));

    // Test edge case for releasing cricketers with mixed case names
    assert(mixedCaseTeam.releaseCricketer("First", "LAST"));
    assert(mixedCaseTeam.cricketerCount() == 1);
    assert(!mixedCaseTeam.rosteredOnCricketTeam("First", "LAST"));

    // Test edge case for substituting cricketers with mixed case names
    assert(mixedCaseTeam.substituteCricketer("first", "last", 3));
    assert(mixedCaseTeam.searchForCricketer("first", "last", value));
    assert(value == 3);

    // Test edge case for releasing all cricketers with mixed case names
    assert(mixedCaseTeam.releaseCricketer("first", "last"));
    assert(mixedCaseTeam.cricketerCount() == 0);
    assert(mixedCaseTeam.noTeam());

    // Test edge case for adding cricketers with spaces in names
    CricketTeam spaceNameTeam;
    assert(spaceNameTeam.addCricketer("First Name", "Last Name", 1));
    assert(spaceNameTeam.addCricketer("Another First", "Another Last", 2));
    assert(spaceNameTeam.cricketerCount() == 2);
    assert(spaceNameTeam.rosteredOnCricketTeam("First Name", "Last Name"));
    assert(spaceNameTeam.rosteredOnCricketTeam("Another First", "Another Last"));

    // Test edge case for releasing cricketers with spaces in names
    assert(spaceNameTeam.releaseCricketer("First Name", "Last Name"));
    assert(spaceNameTeam.cricketerCount() == 1);
    assert(!spaceNameTeam.rosteredOnCricketTeam("First Name", "Last Name"));

    // Test edge case for substituting cricketers with spaces in names
    assert(spaceNameTeam.substituteCricketer("Another First", "Another Last", 3));
    assert(spaceNameTeam.searchForCricketer("Another First", "Another Last", value));
    assert(value == 3);

    // Test edge case for releasing all cricketers with spaces in names
    assert(spaceNameTeam.releaseCricketer("Another First", "Another Last"));
    assert(spaceNameTeam.cricketerCount() == 0);
    assert(spaceNameTeam.noTeam());

    // Test edge case for adding cricketers with hyphens in names
    CricketTeam hyphenNameTeam;
    assert(hyphenNameTeam.addCricketer("First-Name", "Last-Name", 1));
    assert(hyphenNameTeam.addCricketer("Another-First", "Another-Last", 2));
    assert(hyphenNameTeam.cricketerCount() == 2);
    assert(hyphenNameTeam.rosteredOnCricketTeam("First-Name", "Last-Name"));
    assert(hyphenNameTeam.rosteredOnCricketTeam("Another-First", "Another-Last"));

    // Test edge case for releasing cricketers with hyphens in names
    assert(hyphenNameTeam.releaseCricketer("First-Name", "Last-Name"));
    assert(hyphenNameTeam.cricketerCount() == 1);
    assert(!hyphenNameTeam.rosteredOnCricketTeam("First-Name", "Last-Name"));

    // Test edge case for substituting cricketers with hyphens in names
    assert(hyphenNameTeam.substituteCricketer("Another-First", "Another-Last", 3));
    assert(hyphenNameTeam.searchForCricketer("Another-First", "Another-Last", value));
    assert(value == 3);

    // Test edge case for releasing all cricketers with hyphens in names
    assert(hyphenNameTeam.releaseCricketer("Another-First", "Another-Last"));
    assert(hyphenNameTeam.cricketerCount() == 0);
    assert(hyphenNameTeam.noTeam());

    // Example 1
    CricketTeam odOne1, odTwo1, odJoined1;
    odOne1.addCricketer("Trent", "Boult", 18);
    odOne1.addCricketer("Tim", "David", 8);
    odOne1.addCricketer("Rashid", "Khan", 19);

    odTwo1.addCricketer("Trent", "Boult", 18);
    odTwo1.addCricketer("Tim", "Southee", 38);
    odTwo1.addCricketer("Kane", "Williamson", 22);

    // Test merging odOne1 and odTwo1 into odJoined1
    assert(mergeCricketers(odOne1, odTwo1, odJoined1) == true);
    // Verify the number of cricketers in the joined team
    assert(odJoined1.cricketerCount() == 5); // Expecting 5 cricketers
    // Verify each cricketer is present with the correct value
    assert(odJoined1.searchForCricketer("Trent", "Boult", value) && value == 18);
    assert(odJoined1.searchForCricketer("Tim", "David", value) && value == 8);
    assert(odJoined1.searchForCricketer("Rashid", "Khan", value) && value == 19);
    assert(odJoined1.searchForCricketer("Tim", "Southee", value) && value == 38);
    assert(odJoined1.searchForCricketer("Kane", "Williamson", value) && value == 22);

    // Example 2
    CricketTeam odOne2, odTwo2, odJoined2;
    odOne2.addCricketer("Quinton", "DeCock", 12);
    odOne2.addCricketer("Faf", "DuPlessis", 17);
    odOne2.addCricketer("Kagiso", "Rabada", 25);

    odTwo2.addCricketer("Faf", "DuPlessis", 13);
    odTwo2.addCricketer("Virat", "Kohli", 18);

    // Test merging odOne2 and odTwo2 into odJoined2
    assert(mergeCricketers(odOne2, odTwo2, odJoined2) == false);
    // Verify the number of cricketers in the joined team
    assert(odJoined2.cricketerCount() == 3); // Expecting 3 cricketers
    // Verify each cricketer is present with the correct value
    assert(odJoined2.searchForCricketer("Quinton", "DeCock", value) && value == 12);
    assert(odJoined2.searchForCricketer("Kagiso", "Rabada", value) && value == 25);
    assert(odJoined2.searchForCricketer("Virat", "Kohli", value) && value == 18);

    // Example 3: Additional test with odJoined not empty
    CricketTeam odOne3, odTwo3, odJoined3;
    odJoined3.addCricketer("Random", "Player", 99); // This should be cleared by merge

    odOne3.addCricketer("Trent", "Boult", 18);
    odOne3.addCricketer("Tim", "David", 8);
    odOne3.addCricketer("Rashid", "Khan", 19);

    odTwo3.addCricketer("Trent", "Boult", 18);
    odTwo3.addCricketer("Tim", "Southee", 38);
    odTwo3.addCricketer("Kane", "Williamson", 22);

    // Test merging odOne3 and odTwo3 into odJoined3
    assert(mergeCricketers(odOne3, odTwo3, odJoined3) == true);
    // Verify the number of cricketers in the joined team
    assert(odJoined3.cricketerCount() == 5); // Expecting 5 cricketers
    // Verify each cricketer is present with the correct value
    assert(odJoined3.searchForCricketer("Trent", "Boult", value) && value == 18);
    assert(odJoined3.searchForCricketer("Tim", "David", value) && value == 8);
    assert(odJoined3.searchForCricketer("Rashid", "Khan", value) && value == 19);
    assert(odJoined3.searchForCricketer("Tim", "Southee", value) && value == 38);
    assert(odJoined3.searchForCricketer("Kane", "Williamson", value) && value == 22);
}

int main() {
    runTests();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}

