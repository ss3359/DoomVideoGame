#include <iostream> 
#include <stdexcept>
#include <optional>

struct Vector2d
{
    double x; 
    double y;
    Vector2d() = default; 
    Vector2d(double x0, double y0):x(x0), y(y0){}

    
}; 

struct Matrix2d
{
    Vector2d v1, v2; 
    Matrix2d(Vector2d vec1, Vector2d vec2):v1(vec1),v2(vec2){}
    Matrix2d(double a, double b, double c, double d):v1(Vector2d(a,c)), v2(Vector2d(b,d)){}
    Matrix2d() = default; 
    double det()
    {
        double a = this->v1.x, b = this->v2.x, c = this->v1.y, d = this->v2.y; 
        return (a*d)-(b*c); 
    }

    Matrix2d inv()
    {
        double a = this->v1.x, b = this->v2.x, c = this->v1.y, d = this->v2.y; 
        if (abs(this->det()) <= 1e-8)
        {
            throw std::invalid_argument("The Detminant is zero. There this matrix has no inverse!"); 
        }

        double det_mat = this->det();
        return (1.0/det_mat)*Matrix2d(d,-c,-b,a); 
        
    }
}; 

struct Wall 
{
    Vector2d A, B; 
    Wall() = default; 
    Wall(Vector2d a, Vector2d b):
    A(a), B(b){} 
}; 


Vector2d operator+(Vector2d a, Vector2d b)
{
    return Vector2d(b.x + a.x, b.y + a.y); 
}

Vector2d operator-(Vector2d a, Vector2d b)
{
    return Vector2d(b.x - a.x, b.y - a.y); 
}

Vector2d operator*(Matrix2d M, Vector2d b)
{
    double r1 = M.v1.x*b.x + M.v2.x*b.y; 
    double r2 = M.v1.y*b.x + M.v2.y*b.y;
    return Vector2d(r1, r2);
}

Vector2d operator*(double c, Vector2d b)
{
    return Vector2d(c*b.x, c*b.y);
}
Matrix2d operator*(double c, Matrix2d M)
{
    Vector2d c_times_v1 = c*M.v1, c_time_v2=c*M.v2; 
    return Matrix2d(c_times_v1, c_time_v2); 
}
Vector2d ray_segment_intersection(Vector2d player, Vector2d direction, Wall wall)
{
 
    Vector2d w = wall.B - wall.A,b = player - wall.A; 
    Matrix2d M(w, (-1)*direction); 
    Matrix2d invM = M.inv(); 
    
    return invM*b; 

}
std::optional<Vector2d> is_point_of_intersection_valid(Vector2d player, Vector2d direction, Wall wall)
{
    Vector2d result = ray_segment_intersection(player,direction,wall); 
    return (result.x >=0.0 && result.x<1.0 && result.y>=0.0)? false: result; 
}