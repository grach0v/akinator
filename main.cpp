#include "Point.cpp"
#include <vector>

class Akinator
{
    std::vector <Point> vertexes_;
    int cur_;

    operator = (const Akinator&);
    Akinator (const Akinator&);

    public:

    Akinator ();
    bool play();
};

Akinator::Akinator():vertexes_ (), cur_ (0)
{
    vertexes_.push_back (Point (TYPES::Question, 0, "wanna play?"));
}

bool Akinator::play ()
{
    char answer = 0;
    cur_ = 0;

    for (answer = vertexes_[cur_].ask();
         vertexes_[cur_].get (answer) != -1;)
    {
        cur_ = vertexes_[cur_].get (answer);
        answer = vertexes_[cur_].ask();
    }

    if (vertexes_[cur_].get_type() == TYPES::Question)
    {
        std::cout << "tell me whom did u choose\n";
        std::string name;
        std::cin >> name;

        vertexes_[cur_].set (answer, (int)vertexes_.size());
        vertexes_.push_back (Point (TYPES::Object, (int)vertexes_.size(), name));
        cur_ = 0;
    }

    else
    {

        if (answer == ANSWERS::True)
        {
            std::cout << "that was fun\n";
            cur_ = 0;
            return true;
        }

        else
        {
            std::string difference;
            std::string character;
            std::cout << "what the difference between your character and " << vertexes_ [cur_].get_object() << '\n';
            std::cin >> difference;
            std::cout << "what is your character?\n";
            std::cin >> character;

            answer = vertexes_ [cur_].ask (difference + " is it true for ");

            vertexes_ [cur_].set_cur ((int)vertexes_.size());
            Point prev_point = vertexes_ [cur_];
            vertexes_ [cur_] = Point (TYPES::Question, cur_, difference);

            vertexes_ [cur_].set (answer, (int)vertexes_.size());
            vertexes_.push_back (prev_point);

            vertexes_ [cur_].set (invert (answer), (int)vertexes_.size());
            vertexes_.push_back (Point (TYPES::Object, (int)vertexes_.size(), character));

            cur_ = 0;
            return false;
        }
    }

    return false;
}

int main ()
{
    Akinator test;

    while (true)
    {
        test.play ();
    }

    return 0;
}
