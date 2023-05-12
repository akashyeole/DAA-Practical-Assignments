/**
 * @brief This program outputs the solution to a TSP(Travelling Sales Person), taking input from user as a map with edges cost or has default test case. The output to the solution is nearest to the optimal one because of Genetic Alogrithm.
 */


#include<bits/stdc++.h>

#define INF INT_MAX

using namespace std;

/**
 * @brief Represents the indivdual chromosome. Consists of pathString and pathCost for a given a TSP map.
 */
class Chromosome{

    public:
    // Represent the path from city-to-city with start city same as end city.
    string pathString;
    
    // The cost of the given path is the sum of all the subpaths.
    int pathCost;

    /**
     * @brief Default constructor that, initializes the object with default values of pathString "" and pathCost as 0.
     */
    Chromosome(){
        pathString = "";
        pathCost = 0;
    }

    /**
     * @brief Parameteried constructor, constructs a new Chromosome object by initialzing the pathString. 
     * 
     * @param _pathString A path string representing a tour to all the cities from start
     * to end.
     */
    Chromosome(string _pathString){ pathString = _pathString; }

    /**
     * @brief Parameteried constructor, constructs a new Chromosome object by initialzing the pathString and pathCost properties of a class.
     * 
     * @param _pathString A path string representing a tour to all the cities from start to end.
     * @param _pathCost A cost of the tour for the given path string.
     */
    Chromosome(string _pathString, int _pathCost){
        pathString = _pathString;
        pathCost = _pathCost;
    }

    /**
     * @brief Overloaded with << operator to print the state of the object. Prints the pathString and pathCost of the current chromosome.
     * 
     * @param s Implicit ostream object received with overloaded function.
     * @param _chromosome Reference to the object on which the operator is used.
     * @return ostream& Returns the implicit ostream object with formated output to print on console. 
     */
    friend ostream& operator <<(ostream& s, const Chromosome& _chromosome){
        s << "Path String: " << _chromosome.pathString << " |\t " << "Path Cost: " << _chromosome.pathCost;
        return s;
    }
    
};

/**
 * @brief The TSP helps with intializing the TSP problem given the number of cities and a map. Uses the genetic algorithm to solve the problem. Also contains various utility functions which are required through out the process of generating the new chromosome till there mutation. The chromosome on top of the population that survives that till the end of the process is considered as the fittest chromosomes and its path and cost is assigned to the final answer.  
 * 
 */
class TSP{
    
    public:
    
    //  Stores the total number of cities in a map of current instance of TSP.
    int numberOfCities;

    // Vector that stores the cost of an edge/path between pairs of cities of a map. 
    vector<vector<int>> map;

    /**
     * @brief Construct a new TSP object by intializing the values of map and numberOfCities property of the class. Uses the genetic algorithm function to calculate the optimal path of tour.
     * 
     * @param _numberOfCities The number of cities in a map.
     * @param _map Cost of both between each pair of cities in a map.
     */
    TSP(int _numberOfCities, vector<vector<int>>& _map){
        srand(time(0));
        numberOfCities = _numberOfCities;
        map = _map;

        geneticAlgorithm();
    }

    /**
     * @brief The getter function returns the optimal path or tour of all cities.
     * 
     * @return string Path is returned as a string.
     */
    string getOptimalPath(){ return optimalPath; }

    /**
     * @brief The getter function returns the cost of the optimal calculated path.
     * 
     * @return int Cost is returned as an integer.
     */
    int getOptimalPathCost(){ return optimalPathCost; }

    private:

    // Constant variable defining the population size of the chromosomes in a pool.
    const int POPULATION_SIZE = 10;

    // Constant variable defining the city to start tour from. 
    const int START_END_CITY = 0;

    // Constant variable defining the maximum number of generation to perform the mutation.
    const int GENERATION_THRESHOLD = 5;

    // Stores the optimal path or tour of cities.
    string optimalPath = "";

    // Stores the optimal tour's cost starting from start city to the end city of the calculated path.
    int optimalPathCost = INF;

    // Indicates the current generation number.
    int currentGeneration = 1;

    // The cooling variable whose value decreases after every iteration of new generation.
    int temperature = 10000;

    /**
     * @brief Checks if specific character is already present in a given string. Used to check if the selected city is already present in a path.
     * 
     * @param ch A character to be matched in a string. It represents a city.
     * @param str A string where character is to be matched. It represents a path.
     * @return true if character is repeated.
     * @return false otherwise.
     */
    bool isCharRepeated(char ch, string str){
        int n = str.length();
        for(int i = 0; i < n; i+=3) if(str[i] == ch) return true;
        return false;
    }

    /**
     * @brief Generates a random tour path using the number of cities and in-built random functions.
     * 
     * @return string A valid random path of tour.
     */
    string createPathString(){
        string randomPathString = "";
        randomPathString += char(START_END_CITY+65);
        int currLen = 1;
        while(currLen < numberOfCities){
            char currCity = char(((1 + (rand() % (numberOfCities-1))) + 65));
            if(isCharRepeated(currCity, randomPathString)) continue;
            else{
                currLen++;
                randomPathString += "->";
                randomPathString += currCity;
            }
        }
        randomPathString += "->";
        randomPathString += char(START_END_CITY+65);
        return randomPathString;
    }

    /**
     * @brief The function to calculate the cost of the given path of cities in a string using the map / edge adjacency matrix.
     * 
     * @param path A path of tour of cities as a string.
     * @return int A cost path is an integer variable.
     */
    int getPathCost(string path){
        int cost = 0;
        for(int i = 0, k = 0; k < numberOfCities; k++, i+=3){
            int r = path[i] - 65;
            int c = path[i+3] - 65;
            if(map[r][c] == INF) return INF;
            cost += map[r][c];
        }
        return cost;
    }

    /**
     * @brief The function that mutates the string by swapping the two cities except the first and last one.
     * 
     * @param currentPathString The string to be mutated is passed as parameter.
     * @return string The return value is a mutated string.
     */
    string mutatePathString(string currentPathString){
        while(true){
            char cityOne = (1 + (rand() % (numberOfCities-1)));
            char cityTwo = (1 + (rand() % (numberOfCities-1)));
            if(cityOne != cityTwo){
                currentPathString[cityOne*3] ^= currentPathString[cityTwo*3];
                currentPathString[cityTwo*3] ^= currentPathString[cityOne*3];
                currentPathString[cityOne*3] ^= currentPathString[cityTwo*3];
                break;
            }
        }
        return currentPathString;
    }

    /**
     * @brief Heart of the class, the function that uses genetic algorithm to find optimal tour path by creating new generations. Stores the population of chromosomes in a vector, the one at the top after all the iteration is considered as the fittest chromosome or tour with the optimal path. And it updates the optimal path and cost for the given TSP solution in a class. 
     */
    void geneticAlgorithm(){
        auto comp = [](Chromosome &ch1, Chromosome &ch2) { return ch1.pathCost < ch2.pathCost; };
        vector<Chromosome> population;

        // Populating the pool with chromosomes.
        for(int i = 0; i < POPULATION_SIZE; i++){
            string currentPathString = createPathString();
            int currentPathCost = getPathCost(currentPathString);

            Chromosome currentChromosome =  Chromosome(currentPathString, currentPathCost);
            population.push_back(currentChromosome);
        }

        // Printing the population.
        cout << "Initial Population: " << endl;
        for(auto ch: population) cout << ch << endl;
        cout << endl;

        // Performing population crossing and mutation.
        while(temperature > 1000 && currentGeneration <= GENERATION_THRESHOLD){
            sort(population.begin(), population.end(), comp);
            vector<Chromosome> newPopulation;
            for(int i = 0; i < POPULATION_SIZE; i++){
                Chromosome currentChromosome = population[i];

                while(true){
                    // Mutating chromosomes
                    string mutatedPathString = mutatePathString(currentChromosome.pathString);
                    int mutatedPathCost = getPathCost(mutatedPathString);
                    Chromosome mutatedChromosome = Chromosome(mutatedPathString, mutatedPathCost);

                    if(mutatedChromosome.pathCost <= currentChromosome.pathCost){
                        newPopulation.push_back(mutatedChromosome);
                        break;
                    }else{
                        float probability = pow(2.7, -1 * ((float)(mutatedChromosome.pathCost - currentChromosome.pathCost) / temperature));

                        if(probability > 0.5){
                            newPopulation.push_back(mutatedChromosome);
                            break;
                        }
                    }

                }

            }
            // Temperature recaliberation
            temperature = (temperature*90)/100;
            population = newPopulation;

            cout << "Generation " << currentGeneration << " population: " << endl;
            for(auto ch: population) cout << ch << endl;
            cout << endl;
            currentGeneration++; 
        }
        
        // Storing the optimal path  and its cost
        sort(population.begin(), population.end(), comp);
        optimalPath = population[0].pathString;
        optimalPathCost = population[0].pathCost;
        
    }
};


int main(){
    vector<vector<int>> map = { {0, 2, INF, 12, 5},
                                {2, 0, 4, 8, INF},
                                {INF, 4, 0, 3, 3},
                                {12, 8, 3, 0, 10},
                                {5, INF, 3, 10, 0} };
    int numberOfCities = 5;
    TSP testMap = TSP(numberOfCities, map);
    cout << "Optimal path is " << testMap.getOptimalPath() << ", and its cost is " << testMap.getOptimalPathCost() << endl;
    return 0;
}