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
#include <thread>
#include <random>

#define SITE_LIMIT 200
#define DAY_LIMIT 10

using namespace std;

/**
 * Holds a site and its associated information
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

    // Stored upon parsing the input
    static int totalDays;

    /**
     * Returns a list of sites by parsing an input file
     */
    static vector<Site*> readInput(string filename) {

        map<int, Site*> siteMap;

        ifstream infile(filename.c_str());
        string line;

        bool readingLocations = false;

        // Reset totalDays
        InputProcessor::totalDays = 0;

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

                // Update days
                if (day > InputProcessor::totalDays) {
                    InputProcessor::totalDays = day;
                }
            }
        }

        // Return sites
        vector<Site*> sites;

        for (map<int, Site*>::iterator it = siteMap.begin(); it != siteMap.end(); it++) {
            sites.push_back(it->second);
        }

        return sites;
    }

    /**
     * Returns the total number of days in the input file provided
     */
    static int getTotalDays() {
        return InputProcessor::totalDays;
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

    /**
     * Returns the value obtained by following this day plan
     */
    float getPlanValue() {

        float value = 0.0;

        for (deque< Site* >::iterator it = plan.begin(); it != plan.end(); it++) {
            value += (*it)->value;
        }

        return value;
    }
};

/**
 * Stores the final tour plan spanning all days
 */
class TourPlan {
public:
    map<int, VisitPlan> plan;

    /**
     * Adds a visit plan for the given day
     */
    void addPlan(int day, VisitPlan plan) {
        this->plan.insert(make_pair(day, plan));
    }

    /**
     * Fancy printing for debugging
     */
    void print() {
        int day = 1;
    }

    /**
     * Prints the tour plan in the required output format
     */
    void output() {
        for (map<int, VisitPlan>::iterator it = plan.begin(); it != plan.end(); it++) {
            it->second.output();
        }
    }

    /**
     * Returns the value obtained by following this tour plan
     */
    float getPlanValue() {

        float value = 0.0;

        for (map<int, VisitPlan>::iterator it = plan.begin(); it != plan.end(); it++) {
            value += it->second.getPlanValue();
        }

        return value;
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
    static float getTravelTime(Site* site1, Site* site2) {
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
     * Returns the best overall visit plan
     */
    static TourPlan getTourPlan(Touring touring) {

        // Threading limit
        const int THREADS = 4;

        // List of threads and visit plans
        TourPlan plans[THREADS];
        vector<thread*> pthreads;

        // Start processing with multi-threading
        for (int i = 0; i < THREADS; i++) {

            thread* pthread = new thread(getBestPlan, i, plans, touring);
            pthreads.push_back(pthread);
        }

        // Wait for all to complete
        for (int i = 0; i < THREADS; i++) {
            pthreads[i]->join();
        }

        // Pick the best result
        int bestPlanIndex;
        float bestValue = 0.0;
        for (int i = 0; i < THREADS; i++) {
            float currentPlanValue = plans[i].getPlanValue();
            if (currentPlanValue > bestValue) {
                bestValue = currentPlanValue;
                bestPlanIndex = i;
            }
        }

        return plans[bestPlanIndex];
    }

    /**
     * Returns a touring plan
     */
    static void getBestPlan(int id, TourPlan* plans, Touring touring) {

        TourPlan plan;

        // Keep track of sites visited
        map<int, bool> visitedIds;

        int days = InputProcessor::getTotalDays();
        
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

            VisitPlan visitPlan = touring.getDayPlan(i, validSites);

            plan.addPlan(i, visitPlan);
        }

        // Set plan
        plans[id] = plan;
    }

    /**
     * Returns the best touring plan for a given day a list of sites to visit.
     */
    VisitPlan getDayPlan(int day, vector<Site*> sites) {

        // Heuristics
        const int CANDIDATES = 5;
        vector<VisitPlan> visitCandidates;

        VisitPlan bestPlan;

        for (vector<Site*>::iterator it = sites.begin(); it != sites.end(); it++) {

            Site *start = (*it);
            map<int, bool> visited;
            int startTime = start->getOpenTime(day);

            VisitPlan visitPlan = getBestPlanFromSite(startTime, start, sites, visited, day);

            // Maintain candidate list
            if (visitCandidates.size() < CANDIDATES) {
                visitCandidates.push_back(visitPlan);
                make_heap(visitCandidates.begin(), visitCandidates.end(), VisitPlanValueOrdering());
            }
            // Check current is better than top
            // If yes, pop top, insert current into heap
            else if (visitCandidates.size() >= CANDIDATES &&
                visitPlan.value > visitCandidates.front().value) {
                
                pop_heap(visitCandidates.begin(), visitCandidates.end(), VisitPlanValueOrdering());
                visitCandidates.pop_back();

                visitCandidates.push_back(visitPlan);
                push_heap(visitCandidates.begin(), visitCandidates.end(), VisitPlanValueOrdering());

            }
        }

        // Pick the best plan using weighted probability
        // Compute weights
        vector<float> weights;
        float weightSum = 0.0;

        for (vector<VisitPlan>::iterator it = visitCandidates.begin(); 
            it != visitCandidates.end(); it++) {

            float weight = exp( float(day) * (*it).value * (0.01) );

            weights.push_back(weight);
            weightSum += weight;
        }

        // Pick a random element
        random_device rd; // obtain a random number from hardware
        mt19937 eng(rd()); // seed the generator
        uniform_int_distribution<float> distr(0, weightSum);
        float randomNumber = distr(eng);

        for (int i = 0; i < visitCandidates.size(); i++) {

            randomNumber -= weights[i];
            if (randomNumber <= 0) {
                bestPlan = visitCandidates[i];
                break;
            }
        }

        return bestPlan;
    }

    /**
     * Returns the best touring plan, given that we are currently at:
     * site "current", 
     * at time "currentTime", 
     * all potential destination sites (including self) stored in "allSites"
     * having visited the sites stored in "visited",
     * in day "day".
     */
    VisitPlan getBestPlanFromSite(
        float currentTime, Site *current, vector<Site*> allSites, map<int, bool> visited, int day) {

        // Prune the search space. Strategy is specified in get_candidate_sites().
        vector<Site*> sites = get_candidate_sites(current, allSites);
        // vector<Site*> sites = allSites;

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
            float travelTime = Touring::getTravelTime(current, site);
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

    /**
     * Returns a subset of all candidate sites
     * Pruning strategy:
     * To explain :P
     */
    vector<Site*> get_candidate_sites(Site* current, vector<Site*> sites) {

        // Treshold for each heuristic
        float byTimeWeight = 0.3;
        float byValueWeight = 0.3;

        // Get size
        int size = sites.size();
        int limit;

        // Sort by time
        sort(sites.begin(), sites.end(), VisitTimeOrdering(current));
        limit = size * byTimeWeight;
        vector<Site*> timeSortedSites(sites.begin(), sites.begin() + limit);

        // Sort by value
        sort(sites.begin(), sites.end(), ValueOrdering());
        limit = size * byValueWeight;
        vector<Site*> valueSortedSites(sites.begin(), sites.begin() + limit);

        // Merge lists
        vector<Site*> candidates;
        bool siteMap[SITE_LIMIT];

        for (int i = 0; i < SITE_LIMIT; i++) {
            siteMap[i] = false;
        }

        for (vector<Site*>::iterator it = timeSortedSites.begin(); 
            it != timeSortedSites.end(); it++) {
            if (siteMap[(*it)->id] == true) {
                continue;
            }
            candidates.push_back((*it));
        }

        for (vector<Site*>::iterator it = valueSortedSites.begin(); 
            it != valueSortedSites.end(); it++) {
            if (siteMap[(*it)->id] == true) {
                continue;
            }
            candidates.push_back((*it));
        }

        return candidates;
    }

    struct VisitTimeOrdering {

        Site *current;

        VisitTimeOrdering(Site *current) {
            this->current = current;
        }

        bool operator() (Site* site1, Site* site2) {
            return Touring::getTravelTime(site1, current) < Touring::getTravelTime(site2, current);
        }
    };

    struct ValueOrdering {
        bool operator() (Site* site1, Site* site2) {
            return site1->value > site2->value;
        }
    };

    struct VisitPlanValueOrdering {
        bool operator() (VisitPlan plan1, VisitPlan plan2) {
            return plan1.value > plan2.value;
        }
    };
};

int InputProcessor::totalDays = 0;

int main() {

    // Must be changed to read from command line args
    // Get sites from reading the input file
    vector<Site*> sites = InputProcessor::readInput("input.txt");

    // Initialize touring object
    Touring touring(sites);

    // Get tour plan and print
    TourPlan tourPlan = Touring::getTourPlan(touring);
    tourPlan.output();

    return 0;
}
