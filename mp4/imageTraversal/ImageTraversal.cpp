#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal = nullptr;

}

ImageTraversal::Iterator::Iterator(ImageTraversal & t, double tolerance_, PNG some_pic){
  current = t.peek();
  tolerance = tolerance_;
  traversal = &t;
  picture = some_pic;

  for (unsigned i=0; i<picture.width(); i++)
  {
    std::vector<bool>temp;
    for(unsigned j=0; j<picture.height(); j++)
    {
      temp.push_back(false);
    }
    visited.push_back(temp);
  }
  startPixel = picture.getPixel(current.x,current.y);
}

ImageTraversal::~ImageTraversal(){}

ImageTraversal::Iterator::~Iterator(){
  delete traversal;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //traversal->add(Point(x,y));
  if(!traversal->empty())
  {
    unsigned curr_x = current.x;
    unsigned curr_y = current.y;

    visited[curr_x][curr_y]= true;

    curr_x ++;
    if(curr_x < picture.width())
    {
    HSLAPixel &c = picture.getPixel(curr_x,curr_y);
    double limit_ = calculateDelta(startPixel,c);


      if(limit_<tolerance)
      {
        traversal->add(Point(curr_x,curr_y));
      }
    }
    curr_x --;



    curr_y ++;
    if(curr_y < picture.height())
    {
    HSLAPixel &c = picture.getPixel(curr_x,curr_y);
    double limit_ = calculateDelta(startPixel,c);
    if(limit_<tolerance)
    {
      traversal->add(Point(curr_x,curr_y));
    }
    }
    curr_y --;


    if(curr_x != 0)
    {
    curr_x --;
    HSLAPixel &c = picture.getPixel(curr_x,curr_y);
    double limit_ = calculateDelta(startPixel,c);
    if(limit_<tolerance )
    {
      traversal->add(Point(curr_x,curr_y));
    }
    curr_x ++;
    }



    if(curr_y != 0)
    {
    curr_y --;
    HSLAPixel &c = picture.getPixel(curr_x,curr_y);
    double limit_ = calculateDelta(startPixel,c);
    if(limit_<tolerance){
      traversal->add(Point(curr_x,curr_y));
    }
      curr_y ++;
    }


    current=traversal->peek();

    while(visited[current.x][current.y])
    {
      traversal->pop();

      if (traversal->empty()) {
        break;
      }
      current=traversal->peek();

    }

    if (traversal->empty()) {
      delete traversal;
      traversal = nullptr;
    }
  } else {
    delete traversal;
    traversal = nullptr;
  }


return *this;

}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty = false;
  bool otherEmpty = false;

  if(traversal == NULL){thisEmpty = true;}
  if(other.traversal == NULL) {otherEmpty = true;}

  if(!thisEmpty){ thisEmpty = traversal->empty(); }
  if(!otherEmpty){ otherEmpty = other.traversal->empty();}

  if(thisEmpty && otherEmpty) return false;
  else if ((!thisEmpty)&&(!otherEmpty))
  return (traversal != other.traversal);
  else return true;
}
