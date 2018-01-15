#include <iostream>
#include <cassert>
#include "conio.h"

enum TYPES {Question = 0, Object = 1};
enum ANSWERS {True = 0, False = 1, NotStated = 2, Misclicked = 4};

char invert (char answer);

class Point
{
    char type_;
    int cur_point_;
    int yes_point_;
    int no_point_;
    std::string info_;

    public:

    Point ():
    type_ (-1), cur_point_ (-1), yes_point_ (-1), no_point_ (-1), info_ () {}

    Point (char type, int cur_point):
    type_ (type), cur_point_ (cur_point), yes_point_ (-1), no_point_ (-1), info_ () {}

    Point (char type, int cur_point, std::string info):
    type_ (type), cur_point_ (cur_point), yes_point_ (-1), no_point_ (-1), info_ (info) {}

    Point (int cur_point, int yes_point, int no_point, std::string info):
    type_ (TYPES::Question), cur_point_ (cur_point), yes_point_ (yes_point), no_point_ (no_point), info_ (info) {}

    int get_cur () {return cur_point_;}
    int get_yes ();
    int get_no ();
    int get (char answer);
    std::string get_question ();
    std::string get_object ();
    char get_type () {return type_;}

    void set_cur (int that_cur) {cur_point_ = that_cur;}
    void set_yes (int that_yes);
    void set_no (int that_no);
    void set (char answer, int that);
    void set_question (std::string question);
    void set_object (std::string object);

    char ask ();
    char ask (const std::string& message);
    void dump ();
};

//Point get
//{

    int Point::get_yes ()
    {
        assert (type_ == TYPES::Question);
        return yes_point_;
    }

    int Point::get_no ()
    {
        assert (type_ == TYPES::Question);
        return no_point_;
    }

    int Point::get (char answer)
    {
        if (type_ == TYPES::Object) return -1;
        assert (answer == ANSWERS::True || answer == ANSWERS::False);

        switch (answer)
        {
            case ANSWERS::True:
                return yes_point_;

            case ANSWERS::False:
                return no_point_;

            default:
                return -1;
        }
    }

    std::string Point::get_question ()
    {
        assert (type_ == TYPES::Question);
        return info_;
    }

    std::string Point::get_object ()
    {
        assert (type_ == TYPES::Object);
        return info_;
    }

//}

//Point set
//{

    void Point::set_yes (int yes_point)
    {
        assert (type_ == TYPES::Question);
        yes_point_ = yes_point;
    }

    void Point::set_no (int no_point)
    {
        assert (type_ == TYPES::Question);
        no_point_ = no_point;
    }

    void Point::set (char answer, int point)
    {
        assert (type_ == TYPES::Question);
        assert (answer == ANSWERS::True || answer == ANSWERS::False);

        switch (answer)
        {
            case ANSWERS::True:
                yes_point_ = point;
                break;

            case ANSWERS::False:
                no_point_ = point;
                break;

            default:
                break;
        }
    }

    void Point::set_question (std::string question)
    {
        assert (type_ == TYPES::Question);
        info_ = question;
    }

    void Point::set_object (std::string object)
    {
        assert (type_ == TYPES::Object);
        info_ = object;
    }

//}

//Point other
//{

    char Point::ask ()
    {
        //puts ("ask start");
        //dump ();

        if (type_ == TYPES::Object) std::cout << "did you choose ";

        std::cout << info_ << '\n' << "T/F" << '\n'; //will add not stated
        char answer = (char) getch ();

        switch (answer)
        {
            case ('T'):
                return ANSWERS::True;

            case ('t'):
                return ANSWERS::True;

            case ('F'):
                return ANSWERS::False;

            case ('f'):
                return ANSWERS::False;

            default:
                //return ANSWERS::Misclicked;
                ask ();
        }

        return -1;
    }

    char Point::ask (const std::string& message)
    {
        assert (type_ == TYPES::Object);
        std::cout << message;

        std::cout << info_ << '\n' << "T/F" << '\n'; //will add not stated
        char answer = (char) getch ();

        switch (answer)
        {
            case ('T'):
                return ANSWERS::True;

            case ('t'):
                return ANSWERS::True;

            case ('F'):
                return ANSWERS::False;

            case ('f'):
                return ANSWERS::False;

            default:
                //return ANSWERS::Misclicked;
                ask ();
        }

        return -1;
    }


    void Point::dump ()
    {
        printf ("type = %d\nyes_p = %d\nno_p = %d\n", type_, yes_point_, no_point_);
        std::cout << "info = " << info_ << "\n\n\n";
    }

//}

char invert (char answer)
{
    if (answer == ANSWERS::False) return ANSWERS::True;
    if (answer == ANSWERS::True) return ANSWERS::False;

    return -1;
}
