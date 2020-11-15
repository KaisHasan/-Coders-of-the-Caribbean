#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>
using namespace std;


 enum Controller{
     ME=1, ENEMY=0
 };

 class Barrel{
     public:
        int entityID;
        int rumAmount;
        int locX, locY;
        Barrel(int entityID, int rumAmount, int locX, int locY){
            this->rumAmount = rumAmount;
            this->locX = locX;
            this->locY = locY;
        }
 };

 class CanonBall{
     public:
        int entityID;
        int numberOfTurnToImpact;
        CanonBall(int entityID, int numberOfTurnToImpact){
            this->entityID = entityID;
            this->numberOfTurnToImpact = numberOfTurnToImpact;
        }
 };

 class Ship{
    public:
        int entityID;
        int orientation;
        int speed;
        int rumStock;
        Controller controller;
        int locX, locY;
        Ship(int entityID, int locX, int locY, int orientation, int speed, int rumStock, Controller controller){
            this->entityID = entityID;
            this->locX = locX;
            this->locY = locY;
            this->orientation = orientation;
            this->speed = speed;
            this->rumStock = rumStock;
            this->controller = controller;
        }
        double distToBarrel(Barrel barrel){
            return hypot(this->locX - barrel.locX, this->locY - barrel.locY);
        }
        unsigned long squaredDistToBarrel(Barrel barrel){
            return (this->locX - barrel.locX)*(this->locX - barrel.locX) + (this->locY - barrel.locY)*(this->locY - barrel.locY);
        }
        pair<int, int> nextLocation(vector<Barrel> &barrels, vector<Mine> &mines){
            //TODO
        }
 };

int main()
{

    // game loop
    while (1) {
        int myShipCount; // the number of remaining ships
        cin >> myShipCount; cin.ignore();
        int entityCount; // the number of entities (e.g. ships, mines or cannonballs)
        cin >> entityCount; cin.ignore();
        vector<Barrel> barrels;
        vector<Ship> ships;
        for (int i = 0; i < entityCount; i++) {
            int entityId;
            string entityType;
            int x;
            int y;
            int arg1; //the ship's rotation orientation (between 0 and 5) [or  the amount of rum in this barrel if entityType == BARREL
            int arg2; //the ship's speed (between 0 and 2)
            int arg3; //the ship's stock of rum units
            int arg4; //1 if the ship is controlled by you, 0 otherwise
            cin >> entityId >> entityType >> x >> y >> arg1 >> arg2 >> arg3 >> arg4; cin.ignore();
            if(entityType == "BARREL"){
                Barrel barrel = Barrel(entityId, arg1, x, y);
                barrels.push_back(barrel);
            }
            else{
                Controller controller = static_cast<Controller>(arg4);
                Ship ship = Ship(entityId, x, y, arg1, arg2, arg3, controller);
                ships.push_back(ship);
            }
        }
        for (Ship ship : ships) {
            if(ship.controller == ENEMY)
                continue;
            unsigned long minDist = 1<<10;
            int nextX = -1;
            int nextY = -1;
            for (Barrel barrel : barrels){
                unsigned long dist = ship.squaredDistToBarrel(barrel);
                if(minDist > dist){
                    dist = minDist;
                    tie(nextX, nextY) = tie(barrel.locX, barrel.locY);
                }
            }

            if(minDist == 0){
                cout << "WAIT" << endl;
            }
            else{
                cout << "MOVE " << nextX << ' ' << nextY << endl; // Any valid action, such as "WAIT" or "MOVE x y"
            }
        }
    }
}
