#include <gecode/int.hh>
#include <gecode/search.hh>
#include <gecode/minimodel.hh>

using namespace Gecode;
using namespace std;

class BuildingProject : public Space{

protected:

    static const int proj = 15;

    static const int max_no_proj = 9;
    static const int max_budget = 225;
    static const int max_staff = 28;

    //the output arrays

    //a boolean array to store the selected projects
    IntVarArray final_projects;

    //Variable to store the final number for each of projects, budget and staff
    IntVar total_projects;
    IntVar total_budget;
    IntVar total_staff;

    //Variable to hold the objective function
    IntVar total_value;

public:

    BuildingProject():
            final_projects(*this, proj, 0, 1),
            total_projects(*this, 0, max_no_proj),
            total_budget(*this, 0, max_budget),
            total_staff(*this, 0, max_staff),
            total_value(*this, 0, 10000)

    {

        //Value corresponding to each project given as input to the problem
        const int Value[15] = {600, 400, 100, 150, 80, 120, 200, 220, 90, 380, 290, 130, 80, 270, 280};
        const int Budget[15] = {35, 34, 26, 12, 10, 18, 32, 11, 10, 22, 27, 18, 16, 29, 22};
        const int no_of_staff[15] = {5, 3, 4, 2, 2, 2, 4, 1, 1, 5, 3, 2, 2, 4, 3};

        const int not_with[12] = {1, 10, 5, 6, 6, 5, 10, 1, 11, 15, 15, 11};
        const int requires[10] = {3, 15, 4, 15, 8, 7, 13, 2, 14, 2};

        IntArgs proj_values(proj, Value);
        IntArgs proj_Budget(proj, Budget);
        IntArgs proj_staff(proj, no_of_staff);

        IntArgs proj_requires(10, requires);
        IntArgs proj_not_with(12, not_with);

        ///constraints for each project
        //distinct(*this, final_projects);

        rel(*this, total_projects == sum(final_projects));


        linear(*this, proj_staff, final_projects, IRT_EQ, total_staff);
        linear(*this, proj_Budget, final_projects, IRT_EQ, total_budget);
        linear(*this, proj_values, final_projects, IRT_EQ, total_value);
        rel (*this , total_value >= 2370);

        //maximum 9 projects can be selected
        rel(*this, total_projects <= max_no_proj);

        //budget of 225 M€ (million €)
        rel(*this, total_budget <= max_budget);

        //28 staff available
        rel(*this, total_staff <= max_staff);

        //projects not with other projects
        //List: [1, 10, 5, 6, 6, 5, 10, 1, 11, 15, 15, 11]
        for(int i=0; i < 6; i++)
        {
            int j1 = proj_not_with[i*2]-1;
            int j2 = proj_not_with[i*2+1]-1;
            rel(*this, final_projects[j1]  + final_projects[j2] <= 1);
        }

        //project that require some projects
        //List: [3, 15, 4, 15, 8, 7, 13, 2, 14, 2];
        for(int i=0; i < 5; i++)
        {
            int j1 = proj_requires[i*2]-1;
            int j2 = proj_requires[i*2+1]-1;
            rel(*this, final_projects[j1] - final_projects[j2] <= 0);
        }
        branch(*this, final_projects, INT_VAR_MAX_MAX(), INT_VAL_MAX());
    }

    /// Constructor for cloning \a s
    // search support and update for all five variable arrays
    BuildingProject (bool share, BuildingProject& s) : Space(share, s)
    {
        final_projects.update(*this, share, s.final_projects);
        total_projects.update(*this, share, s.total_projects);
        total_budget.update(*this, share, s.total_budget);
        total_staff.update(*this, share, s.total_staff);
        total_value.update(*this, share, s.total_value);
    }

    /// Copy during cloning
    virtual Space* copy(bool share) {
        return new BuildingProject(share,*this);
    }

    /// Print solution
    void print(void)
    {

        string project_names[15] = { "Ishall", "sporthall", "Hotell", "Restaurant", "Kontor_A",
                                     "Kontor_B", "Skola", "Dagis", "Lager", "Simhall", "Hyreshus",
                                     "Bilverstad", "Tennishall", "Idrottsanl", "Baythamn"};

        cout << "Final Selected Projects:" << final_projects << endl;
        cout << "Total Value of selected Project: " << total_value << endl;
        cout << "Total Staff for selected Projects: " << total_staff << endl;
        cout << "Total Budget of all Projects : " << total_budget << endl;
        cout << "Total number of projects: " << total_projects << endl;
        cout << "The following projects should be selected" << endl;
        for (int i = 0; i < proj; i++) {
            if (final_projects[i].val () == 1) {
                cout << i + 1 << " ";
                int project_index = i;
                cout<<project_names[i]<<" ";
            }
        }
    }
};

int main(int argc, char* argv[])
{
    //create model and search engine
    BuildingProject *b = new BuildingProject();
    BAB<BuildingProject> e(b);
    delete b;

    //search and print the result
    while (BuildingProject * s = e.next()) {
        s->print();
        delete s;
    }
    return 0;
}
