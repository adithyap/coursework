#include <iostream>
#include <cstdio>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <queue>

using namespace std;

/**
 * Holds a site and the associated information
 */
class Site {

public:
    int id;
    int avenue;
    int street;
    float desiredTime;
    float value;

    map< int, pair<int, int> > openHours;

    Site(int id) {
        this->id = id;
    }

    /**
     * Sets the location of this site
     */
    void setLocation(int avenue, int street, float desiredTime, float value) {
        this->avenue = avenue;
        this->street = street;
        this->desiredTime = desiredTime / 60.0; // Convert to minutes
        this->value = value;
    }

    /**
     * Adds an open hour entry (day, opening time, closing time)
     */
    void addOpenHours(int day, int start, int end) {
        this->openHours.insert(make_pair(day, make_pair(start, end)));
    }

    /**
     * Returns if the site is open on a particular day
     */
    bool isOpen(int day) {
        return openHours.find(day) != openHours.end();
    }

    /**
     * Returns the time when the site opens on a particular day
     */
    int getOpenTime(int day) {
        if (isOpen(day)) {
            return openHours[day].first;
        }

        return -1;
    }

    /**
     * Returns the time when the site closes on a particular day
     */
    int getCloseTime(int day) {
        if (isOpen(day)) {
            return openHours[day].second;
        }

        return -1;
    }

    /**
     *  Fancy print for debugging
     */
    void print() {
        printf("---------------------------------------------------------------\n");
        printf("ID: %d, Avenue: %d, Street: %d, Desired Time: %f, Value: %f\n", 
            id, avenue, street, desiredTime, value);
        
        for (map< int, pair<int, int> >::iterator it = openHours.begin(); 
            it != openHours.end(); it++) {

            printf("Day %d, Start: %d, End: %d\n", it->first, it->second.first, it->second.second);
        }
        printf("---------------------------------------------------------------\n");
    }
};

/**
 * Provides static helpers to read input file
 */
class InputProcessor {

public:
    /**
     * Returns a list of sites by parsing an input file
     */
    static vector<Site*> readInput(string filename) {

        map<int, Site*> siteMap;

        ifstream infile(filename.c_str());
        string line;

        bool readingLocations = false;

        while(getline(infile, line)) {
            if (line.size() == 0) {
                continue;
            }

            // Check for string, string indicates a header
            // Read locations first
            // When a header is encountered again, read open hours
            if (isalpha(line[0])) {
                readingLocations = !readingLocations;
                continue;
            }

            // Get tokens
            std::vector<std::string> tokens = split(line, ' ');

            // Parse strings
            int siteID = getIntFromString(tokens[0]);

            if (readingLocations) {

                int avenue = getIntFromString(tokens[1]);
                int street = getIntFromString(tokens[2]);
                float desiredTime = getFloatFromString(tokens[3]);
                float value = getFloatFromString(tokens[4]);

                Site* site = new Site(siteID);
                site->setLocation(avenue, street, desiredTime, value);

                // Add to map
                siteMap.insert(make_pair(siteID, site));
            } else {

                int day = getIntFromString(tokens[1]);
                int start = getIntFromString(tokens[2]);
                int end = getIntFromString(tokens[3]);

                // Add open hours
                siteMap[siteID]->addOpenHours(day, start, end);
            }
        }

        // Return sites
        vector<Site*> sites;

        for (map<int, Site*>::iterator it = siteMap.begin(); it != siteMap.end(); it++) {
            sites.push_back(it->second);
        }

        return sites;
    }

private:

    /**
     * Returns an integer by parsing a string
     */
    static int getIntFromString(string value) {
        return strtol(value.c_str(), NULL, 10);
    }

    /**
     * Returns a float by parsing a string
     */
    static float getFloatFromString(string value) {
        return strtof(value.c_str(), NULL);
    }

    /**
     * Splits a string into tokens, with the specified delimiter
     */
    static vector<string> &split(const string &s, char delim, vector<string> &elems) 
    {
        stringstream ss(s);
        string item;
        
        while (getline(ss, item, delim)) 
        {
            elems.push_back(item);
        }

        return elems;
    }

    /**
     * Splits a string into tokens, with the specified delimiter
     */
    static vector<string> split(const string &s, char delim) 
    {
        vector<string> elems;
        split(s, delim, elems);
        return elems;
    }
};

/**
 * Stores the final site visit plan for a single day
 */
class VisitPlan {
public:
    float value;
    deque<Site*> plan;

    VisitPlan() {
        this->value = 0.0;
    }

    /**
     * Fancy printing for debugging
     */
    void print() {
        printf("Tour Plan: ");
        output();
        printf("Value: %f\n", value);
    }

    /**
     * Prints the visit plan in the required output format
     */
    void output() {
        for (deque< Site* >::iterator it = plan.begin(); it != plan.end(); it++) {
            printf("%d ", (*it)->id);
        }
        printf("\n");
    }
};

/**
 * Computes optimal (hopefully) touring path
 */
class Touring {

public:
    vector<Site*> sites;

    Touring(vector<Site*> sites) {
        this->sites = sites;
    }

    /**
     * Returns the time taken to travel from site 1 to site 2
     */
    float getTravelTime(Site* site1, Site* site2) {
        // Convert to minutes and return
        return
            float(abs(site1->avenue - site2->avenue) + abs(site1->street - site2->street)) / 60.0;
    }

    /**
     * Returns the sites that are open in the given day, and,
     * are open for longer than the desired time to visit the site.
     */
    vector<Site*> getOpenSitesByDay(int day) {
        vector<Site*> openSites;

        for (vector<Site*>::iterator it = sites.begin(); it != sites.end(); it++) {

            if ((*it)->isOpen(day)) {
                int openDuration = (*it)->getCloseTime(day) - (*it)->getOpenTime(day);

                if (openDuration > (*it)->desiredTime) {
                    openSites.push_back((*it));
                }
            }
        }

        return openSites;
    }

    /**
     * Returns the value obtained by visiting a list of sites
     */
    int getPlanValue(vector<Site*> sites) {

        double value = 0.0;

        for (vector<Site*>::iterator it = sites.begin(); it != sites.end(); it++) {

            value += (*it)->value;
        }

        return value;
    }

    /**
     * Returns the best touring plan for a given day a list of sites to visit
     */
    VisitPlan getDayPlan(int day, vector<Site*> sites) {

        VisitPlan bestPlan;

        for (vector<Site*>::iterator it = sites.begin(); it != sites.end(); it++) {

            Site *start = (*it);
            map<int, bool> visited;
            int startTime = start->getOpenTime(day);

            VisitPlan visitPlan = getBestPlanFromSite(startTime, start, sites, visited, day);

            if (visitPlan.value > bestPlan.value) {
                bestPlan.value = visitPlan.value;
                bestPlan.plan = visitPlan.plan;
            }
        }

        return bestPlan;
    }

    /**
     * Returns the best touring plan, given that we are currently at:
     * site "current", 
     * at time "currentTime", 
     * all potential destination sites (including self) stored in "sites"
     * having visited the sites stored in "visited",
     * in day "day".
     */
    VisitPlan getBestPlanFromSite(
        float currentTime, Site *current, vector<Site*> sites, map<int, bool> visited, int day) {

        VisitPlan bestPlan;

        // If we have reached before the start time, wait till the start time
        if (currentTime < current->getOpenTime(day)) {
            currentTime = current->getOpenTime(day);
        }

        // Mark this site as visited
        visited.insert(make_pair(current->id, true));

        // Leaving time is the start time + desired stay time at the site
        float leavingTime = currentTime + current->desiredTime;

        // Compute the best plan
        for (vector<Site*>::iterator it = sites.begin(); it != sites.end(); it++) {

            Site *site = (*it); // For simplicity

            // Check if the site is already visited
            if (visited.find(site->id) != visited.end()) {
                continue;
            }

            // Get travel time to the new site
            // Compute the earliest time we can reach the next site
            float travelTime = getTravelTime(current, site);
            float reachTime = leavingTime + travelTime;

            // Compute the time to reach the new site by, so that the desired time
            // can be sepent there. If it is not possible to spend the desired time,
            // there is no point in going to the new site.
            float minReachTime = site->getCloseTime(day) - site->desiredTime;

            if (reachTime <= minReachTime) {

                VisitPlan visitPlan = getBestPlanFromSite(reachTime, site, sites, visited, day);

                if (visitPlan.value > bestPlan.value) {
                    bestPlan.value = visitPlan.value + current->value;
                    bestPlan.plan = visitPlan.plan;
                }
            }
        }

        // If there are no visitable sites, 
        // return the value of this site and add itself in the best_plan.
        if (bestPlan.value == 0.0) {
            bestPlan.value = current->value;
        }

        // Add this site to the best plan originating from this site
        bestPlan.plan.push_front(current);

        return bestPlan;
    }
};

int main() {

    // Must be changed to read from command line args
    // Get sites from reading the input file
    vector<Site*> sites = InputProcessor::readInput("input.txt");

    // Initialize touring object
    Touring touring(sites);

    // Keep track of sites visited
    map<int, bool> visitedIds;

    // TODO: Get days from input processing
    int days = 3;
    
    // Day level greedy algorithm
    // For a given day, choose the best touring strategy
    for (int i = 1; i <= days; i++) {

        // Get all open sites for this day
        vector<Site*> candidates = touring.getOpenSitesByDay(i);
        vector<Site*> validSites;

        // Sites that are visited in a previous day are no longer valid
        for (vector<Site*>::iterator it = candidates.begin(); it != candidates.end(); it++) {
            if (visitedIds.find((*it)->id) == visitedIds.end() ) {
                validSites.push_back((*it));   
            }
        }
        
        // Get visit plan and print plan for the day
        VisitPlan visitPlan = touring.getDayPlan(i, validSites);
        visitPlan.output();

        // Mark visited sites
        for (deque< Site* >::iterator it = visitPlan.plan.begin(); 
            it != visitPlan.plan.end(); it++) {
            visitedIds.insert(make_pair((*it)->id, true));
        }
    }

    return 0;
}
