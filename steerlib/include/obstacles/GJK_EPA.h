/*!
*
* \author VaHiD AzIzI
*
*/


#ifndef GJK_EPA_H_
#define GJK_EPA_H_


#include "util/Geometry.h"


#include <vector>


namespace SteerLib
{

    class GJK_EPA
    {
        public:
            GJK_EPA();

            /*!
             * \brief Do NOT CHANGE intersect FUNCTION!!!
             *
             *        Please NOTE the intersect function is STATIC
             *        If there is a collision the return value of intersect is TRUE, else FALSE
             *        You are free to add everything that you want to this class not other places
             *        Type of vertices are Vector which you can check Vector class in util/Geometry.h to get familier with overloaded operators
             *
             *        You need to recognize that there is collision or not, if yes you need to print out the collision information...
             *        (collision vector, collision depth(penetration) )
             *
             *        intersection will be callsed between all polygons, it means if we have 3 polygons it is called 3 times...
             *        one between polygon No. 1 and No. 2 ...
             *        one between polygon No. 1 and No. 3 ...
             *        one between polygon No. 2 and No. 3
             *
             *        For grading your results will be compared by our results with testcase polygons1, so please run your code with...
             *        original version of polygon1
             */
            static bool intersect(const std::vector<Util::Vector>&,const std::vector<Util::Vector>&);

        private:

    }; // class GJK_EPA

} // namespace SteerLib


#endif /* GJK_EPA_H_ */
