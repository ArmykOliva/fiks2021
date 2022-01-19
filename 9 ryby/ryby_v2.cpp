// A C++ program to check if two given line segments intersect
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Každý bod má 2d souřadnice a každá úsečka má 2 body
struct Point
{
	int x;
	int y;
};
struct Line
{
	Point p1;
	Point p2;
};

//Jsou-li zadány tři kolineární body p, q, r, funkce ověří, zda bod q leží na úsečce "pr".
bool onSegment(Point p, Point q, Point r) {
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;

	return false;
}

//Dostat orientaci tří bodů p, q, r.
// Funkce vrací:
// 0 --> p, q a r jsou kolineární
// 1 --> Po směru hodinových ručiček
// 2 --> Proti směru hodinových ručiček
int orientation(Point p, Point q, Point r) {
	int val = (q.y - p.y) * (r.x - q.x) -
			  (q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0; // kolineární

	return (val > 0)? 1: 2; // proti nebo po směru
}

//Hlavní fuknce, která zjistí zda se úsečka p1q1 protíná s úsečkou p2q2
bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
	// Najdeme čtyři potřebné orientace pro obecné a speciální případy
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// Obecný případ
	if (o1 != o2 && o3 != o4)
		return true;

	// Speciální případ
	// p1, q1 a p2 jsou kolineární a p2 leží na úsečce p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 a q2 jsou kolineární a q2 leží na úsečce p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 a p1 jsou kolineární a p1 leží na úsečce p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 a q1 jsou kolineární a q1 leží na úsečce p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Nespadá do žádného z výše uvedených případů
}

//Funkce která čte řádek standartního vstupu a načítá ho do vektoru čísel
vector<int> fiks_parser() {
	string line;
    vector<int> input;
    getline(cin,line);
	string space_delimiter = " ";
    size_t pos = 0;
    while ((pos = line.find(space_delimiter)) != string::npos) {
		int num = stoi(line.substr(0, pos));
        input.push_back(num);
        line.erase(0, pos + space_delimiter.length());
    }
	input.push_back(stoi(line));

	return input;
}

//Funkce, která zjistí kolik polygonů se dotýká úsečka s
int get_collisions(Line s,vector<vector<Line>> polygons) {
	//Iterujeme přes všechny polygony a počítáme kolik z nich se protnou
	unsigned int collisions = 0;
	for (vector<Line> &polygon : polygons) {
		//Zjistíme zda se úsečka s dotýka alespoň jedné úsečky z polygonu
		for (Line &l : polygon) {
			if (doIntersect(s.p1, s.p2, l.p1, l.p2)) {
				collisions ++;
				break;
			}
		}
		if (collisions == polygons.size()) break;
	}
	return collisions;
}

//Program
int main()
{
	//Dostat data z první řádky
    vector<int> in = fiks_parser();
	int N = in[0];

	//Init polygonů, maximálních souřadnic a směru
	vector<vector<Line>> polygons;
	int maxx = 1, maxy = 1;
	Point dir = {in[1],in[2]};

	//Parse všech polygonů ze strandartního vstupu do polygons
	for (int i = 0; i < N; i++) {
		vector<int> coords = fiks_parser();
		vector<Line> polygon;
		for (int j = 1; j < coords.size(); j += 2) {
			int x1=coords[j],y1=coords[j+1],x2=coords[j+2],y2=coords[j+3];
			if (j + 2 >= coords.size()) { x2 = coords[1]; y2 = coords[2]; } //Pokud neexistují žádné další body, druhá část úsečky je první bod
			if (x1 > maxx) maxx = x1; if (y1 > maxy) maxy = y1; //Dostat maximální souřadnice
			polygon.push_back({x1,y1,x2,y2});
		}
		polygons.push_back(polygon);
	}

	unsigned int maxcollisions = 0;
	for (vector<Line> &polygon : polygons) {
		//Zjistíme zda se úsečka s dotýka alespoň jedné úsečky z polygonu
		for (Line &l : polygon) {
			///Úsečka s od bodu xxx,yyy podle směru dir
			Line s = {{dir.x*min(-maxx,-maxy)+l.p1.x,dir.y*min(-maxx,-maxy)+l.p1.y},{dir.x*max(maxx,maxy)+l.p1.x,dir.y*max(maxx,maxy)+l.p1.y}};
			//pro první bod v úsečce
			unsigned int collisions = get_collisions(s,polygons);
			maxcollisions = max(collisions,maxcollisions);
			//pro druhý bod v úsečced
			s = {{dir.x*min(-maxx,-maxy)+l.p2.x,dir.y*min(-maxx,-maxy)+l.p2.y},{dir.x*max(maxx,maxy)+l.p2.x,dir.y*max(maxx,maxy)+l.p2.y}};
			collisions = get_collisions(s,polygons);
			maxcollisions = max(collisions,maxcollisions);
		}
	}
	cout << maxcollisions << endl;

	return 0;
}
