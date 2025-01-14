#include "Plotter.h"
#include "strlib.h"
#include "vector.h"
using namespace std;
void motivation(string str, double &x, double &y, const Vector<string> &v, bool penstatus, const PenStyle &pen);
void motivation(string str, bool &penstatus);
void motivation(string str, PenStyle &pen, const Vector<string> &v);

void runPlotterScript(istream& input) {
    /* TODO: Delete this line and the one after it, then implement this function. */
    double x=0,y=0;
    PenStyle pen = PenStyle{1, "black"};
    bool penstatus =false;
    for(string line; getline(input, line);)
    {
        Vector<string> v = stringSplit(line, " ");
        string str = toLowerCase(v[0]);
        if(v.size() == 1){
            motivation(str, pen, v);
        }else if(v.size() == 2){
           motivation(str, penstatus );
        }else{
            motivation(str, x, y, v, penstatus, pen);
        }

    }
}
void motivation(string str, double &x, double &y, const Vector<string> &v, bool penstatus, const PenStyle &pen)
{
    double n1 = stringToReal(v[1]);
    double n2 = stringToReal(v[2]);

    if(str == "moveabs"){
        if(penstatus){
            drawLine(x, y, n1, n2, pen);
        }
        x = n1;
        y = n2;
    }else if(str == "moverel"){
        if(penstatus){
            drawLine(x, y, x+n1, y+n2, pen);
        }
        x+=n1;
        y+=n2;
    }
}

void motivation(string str, bool &penstatus){
    if(str == "penup")
        penstatus = false;
    else if(str == "pendown"){
        penstatus = true;
    }
}
void motivation(string str, PenStyle &pen, const Vector<string> &v){
    if(str == "pencolor"){
        pen.color = v[1];
    }else if(str == "penwidth"){
        pen.width = stringToReal(v[1]);
    }
}
