#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

// ================================================================
//  ANSI COLORS
// ================================================================
#define RST     "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define GREEN   "\033[92m"
#define YELLOW  "\033[93m"
#define RED     "\033[91m"
#define CYAN    "\033[96m"
#define PURPLE  "\033[95m"

string green(const string& t)  { return string(GREEN)  + t + RST; }
string yellow(const string& t) { return string(YELLOW) + t + RST; }
string red(const string& t)    { return string(RED)    + t + RST; }
string cyan(const string& t)   { return string(CYAN)   + t + RST; }
string purple(const string& t) { return string(PURPLE) + t + RST; }
string bold(const string& t)   { return string(BOLD)   + t + RST; }
string dim(const string& t)    { return string(DIM)    + t + RST; }

// ================================================================
//  PLAYER STRUCTURE
// ================================================================
struct Player {
    string name;
    int    cost;
    int    rating;
    string role;
    string country;
    int    bat;
    int    bowl;
    int    field;
};

// ================================================================
//  PLAYER DATABASE
// ================================================================
vector<Player> get_player_pool() {
    return {
        // Batsmen
        {"Virat Kohli",        15, 95, "Batsman",       "India",       95, 10, 90},
        {"Rohit Sharma",       14, 92, "Batsman",       "India",       92, 15, 85},
        {"David Warner",       12, 88, "Batsman",       "Australia",   88,  5, 82},
        {"Kane Williamson",    11, 87, "Batsman",       "New Zealand", 87, 20, 80},
        {"Babar Azam",         13, 90, "Batsman",       "Pakistan",    90,  5, 83},
        {"Steve Smith",        10, 85, "Batsman",       "Australia",   85, 18, 78},
        {"Shubman Gill",        8, 80, "Batsman",       "India",       80,  5, 85},
        {"KL Rahul",           11, 83, "WK-Batsman",    "India",       83,  0, 88},
        // All-Rounders
        {"Ben Stokes",         14, 93, "All-Rounder",   "England",     85, 80, 90},
        {"Hardik Pandya",      13, 88, "All-Rounder",   "India",       80, 75, 85},
        {"Shakib Al Hasan",     9, 84, "All-Rounder",   "Bangladesh",  75, 82, 78},
        {"Ravindra Jadeja",    12, 89, "All-Rounder",   "India",       72, 85, 95},
        {"Marcus Stoinis",      7, 76, "All-Rounder",   "Australia",   74, 70, 80},
        {"Mitchell Marsh",      8, 78, "All-Rounder",   "Australia",   76, 72, 78},
        // Wicket Keepers
        {"MS Dhoni",           12, 91, "Wicket Keeper", "India",       80,  0, 98},
        {"Jos Buttler",        13, 90, "Wicket Keeper", "England",     88,  0, 90},
        {"Rishabh Pant",       11, 85, "Wicket Keeper", "India",       83,  0, 87},
        {"Quinton de Kock",     9, 82, "Wicket Keeper", "S. Africa",   80,  0, 85},
        // Bowlers
        {"Jasprit Bumrah",     14, 95, "Bowler",        "India",       10, 95, 80},
        {"Pat Cummins",        13, 92, "Bowler",        "Australia",   25, 92, 82},
        {"Mitchell Starc",     11, 88, "Bowler",        "Australia",   20, 88, 78},
        {"Kagiso Rabada",      10, 87, "Bowler",        "S. Africa",   18, 87, 75},
        {"Shaheen Afridi",      9, 85, "Bowler",        "Pakistan",    12, 85, 72},
        {"Trent Boult",         8, 83, "Bowler",        "New Zealand", 15, 83, 74},
        {"Ravichandran Ashwin",10, 86, "Bowler",        "India",       35, 86, 70},
        {"Adil Rashid",         6, 75, "Bowler",        "England",     20, 75, 70},
        {"Yuzvendra Chahal",    7, 78, "Bowler",        "India",        8, 78, 72},
        {"Wanindu Hasaranga",   8, 80, "Bowler",        "Sri Lanka",   30, 80, 75},
    };
}

// ================================================================
//  HELPERS
// ================================================================
string role_icon(const string& role) {
    if (role == "Batsman" || role == "WK-Batsman") return "[BAT]";
    if (role == "All-Rounder")                     return "[AR] ";
    if (role == "Wicket Keeper")                   return "[WK] ";
    if (role == "Bowler")                          return "[BWL]";
    return "[?]  ";
}

string rating_color(int r) {
    string s = to_string(r);
    if (r >= 90) return green(s);
    if (r >= 80) return yellow(s);
    return red(s);
}

bool player_in(const vector<Player>& vec, const Player& p) {
    for (auto& x : vec)
        if (x.name == p.name) return true;
    return false;
}

void print_line(char ch = '-', int len = 65) {
    cout << string(len, ch) << "\n";
}

void print_header() {
    cout << "\n" << BOLD << CYAN;
    print_line('=');
    cout << "   [CRICKET]  CRICKET TEAM SELECTOR  [TROPHY]\n";
    cout << "   IPL-Style Auction -- DP Knapsack Algorithm\n";
    print_line('=');
    cout << RST << "\n";
}

void print_section(const string& title) {
    cout << "\n" << BOLD << "-- " << title << " ";
    int dashes = 55 - (int)title.size();
    if (dashes > 0) cout << string(dashes, '-');
    cout << RST << "\n";
}

string progress_bar(int value, int total, int width = 40) {
    double pct = min((double)value / total, 1.0);
    int filled = (int)(pct * width);
    string bar = green(string(filled, '#')) + dim(string(width - filled, '.'));
    char buf[16]; sprintf(buf, "%.1f%%", pct * 100);
    return "[" + bar + "] " + buf;
}

// ================================================================
//  PRINT PLAYER TABLE
// ================================================================
void print_player_table(const vector<Player>& players, bool show_index = true) {
    cout << "  " << left
         << setw(4)  << "#"
         << setw(24) << "Name"
         << setw(16) << "Role"
         << setw(14) << "Country"
         << setw(10) << "Cost"
         << "Rating\n";
    cout << dim("  " + string(72, '-')) << "\n";
    for (int i = 0; i < (int)players.size(); i++) {
        auto& p = players[i];
        string idx = show_index ? to_string(i + 1) : "*";
        cout << "  " << left
             << setw(4)  << idx
             << setw(24) << p.name
             << setw(16) << (role_icon(p.role) + " " + p.role.substr(0, 8))
             << setw(14) << p.country
             << setw(10) << yellow("Rs." + to_string(p.cost) + "Cr")
             << rating_color(p.rating) << "\n";
    }
}

// ================================================================
//  0/1 KNAPSACK -- DYNAMIC PROGRAMMING
// ================================================================
struct KnapsackResult {
    int            total_rating;
    vector<Player> selected;
    vector<Player> not_selected;
};

KnapsackResult knapsack(const vector<Player>& players, int budget, int max_players = 11) {

    // Step 1: Mandatory role picks (sorted by highest rating)
    vector<Player> mandatory;
    int rem = budget;

    auto pick_mandatory = [&](const string& role_match, int count) {
        vector<Player> pool;
        for (auto& p : players) {
            bool match =
                (role_match == "Batsman"       && (p.role == "Batsman" || p.role == "WK-Batsman")) ||
                (role_match == "Wicket Keeper" && p.role == "Wicket Keeper") ||
                (role_match == "All-Rounder"   && p.role == "All-Rounder")   ||
                (role_match == "Bowler"        && p.role == "Bowler");
            if (match && !player_in(mandatory, p) && p.cost <= rem)
                pool.push_back(p);
        }
        sort(pool.begin(), pool.end(),
             [](const Player& a, const Player& b){ return a.rating > b.rating; });
        int picked = 0;
        for (auto& p : pool) {
            if (picked >= count) break;
            mandatory.push_back(p);
            rem -= p.cost;
            picked++;
        }
    };

    pick_mandatory("Batsman",       3);
    pick_mandatory("Wicket Keeper", 1);
    pick_mandatory("All-Rounder",   2);
    pick_mandatory("Bowler",        4);

    // Step 2: DP on remaining players to fill leftover slots
    vector<Player> remaining;
    for (auto& p : players)
        if (!player_in(mandatory, p)) remaining.push_back(p);

    int slots_left = max_players - (int)mandatory.size();
    int n = (int)remaining.size();
    int W = (rem > 0) ? min(rem, 300) : 0; // guard against negative budget after mandatory

    // dp[i][w] = {max_rating, count_of_players}
    vector<vector<pair<int,int>>> dp(n + 1, vector<pair<int,int>>(W + 1, {0, 0}));
    vector<vector<bool>> chose(n + 1, vector<bool>(W + 1, false));

    for (int i = 1; i <= n; i++) {
        int cost   = remaining[i-1].cost;
        int rating = remaining[i-1].rating;
        for (int w = 0; w <= W; w++) {
            dp[i][w]    = dp[i-1][w];
            chose[i][w] = false;
            if (cost <= w) {
                int new_r = dp[i-1][w-cost].first  + rating;
                int new_c = dp[i-1][w-cost].second + 1;
                if (new_c <= slots_left && new_r > dp[i][w].first) {
                    dp[i][w]    = {new_r, new_c};
                    chose[i][w] = true;
                }
            }
        }
    }

    // Backtrack to find which players were chosen
    vector<Player> extra;
    int w = W;
    for (int i = n; i >= 1; i--) {
        if (chose[i][w]) {
            extra.push_back(remaining[i-1]);
            w -= remaining[i-1].cost;
        }
    }

    vector<Player> selected = mandatory;
    for (auto& p : extra) selected.push_back(p);

    vector<Player> not_selected;
    for (auto& p : players)
        if (!player_in(selected, p)) not_selected.push_back(p);

    int total_rating = 0;
    for (auto& p : selected) total_rating += p.rating;

    return {total_rating, selected, not_selected};
}

// ================================================================
//  GREEDY SUGGESTION
// ================================================================
string greedy_suggestion(const vector<Player>& not_selected, int remaining_budget) {
    if (not_selected.empty()) return "Perfect squad selected!";

    Player best = not_selected[0];
    double best_ratio = 0;
    for (auto& p : not_selected) {
        double ratio = (double)p.rating / p.cost;
        if (ratio > best_ratio) { best_ratio = ratio; best = p; }
    }
    int shortfall = best.cost - remaining_budget;
    char buf[8]; sprintf(buf, "%.1f", best_ratio);
    string tip = "Best available: " + best.name + " (" + best.role + ")"
               + " -- Rating/Cost ratio: " + buf + ". ";
    if (shortfall > 0)
        tip += "Need Rs." + to_string(shortfall) + "Cr more to afford them.";
    else
        tip += "You can afford them! Rs." + to_string(remaining_budget) + "Cr remaining.";
    return tip;
}

// ================================================================
//  TEAM BALANCE CHECK
// ================================================================
struct RoleCount { int batsmen = 0, allrounders = 0, keepers = 0, bowlers = 0; };

RoleCount check_team_balance(const vector<Player>& selected) {
    RoleCount rc;
    for (auto& p : selected) {
        if      (p.role == "Batsman" || p.role == "WK-Batsman") rc.batsmen++;
        else if (p.role == "All-Rounder")                        rc.allrounders++;
        else if (p.role == "Wicket Keeper")                      rc.keepers++;
        else if (p.role == "Bowler")                             rc.bowlers++;
    }
    return rc;
}

// ================================================================
//  MAIN
// ================================================================
int main() {
    print_header();

    vector<Player> players = get_player_pool();

    // Show full player pool
    print_section("AVAILABLE PLAYER POOL");
    cout << "  Total Players: " << cyan(to_string(players.size())) << "\n\n";
    print_player_table(players, false);

    // Budget input
    print_section("AUCTION BUDGET SETUP");
    cout << dim("  Like IPL -- Set your total budget to buy 11 players\n\n");

    int budget = 0;
    while (true) {
        cout << bold("  Enter total auction budget (Rs. Crores, e.g. 90): Rs.");
        if (cin >> budget && budget > 0) break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << red("  Enter a valid positive number.\n");
    }

    int total_pool_cost = 0;
    for (auto& p : players) total_pool_cost += p.cost;

    cout << "\n  Your Budget      : " << green("Rs." + to_string(budget) + " Crores") << "\n";
    cout << "  Total Pool Value : " << yellow("Rs." + to_string(total_pool_cost) + " Crores") << "\n";
    cout << "  Max Players      : " << cyan("11") << "\n";

    cout << bold("\n  Press Enter to run DP Team Selection...");
    cin.ignore(); cin.get();

    // Run Knapsack DP
    KnapsackResult result = knapsack(players, budget, 11);

    int total_spent = 0;
    for (auto& p : result.selected) total_spent += p.cost;
    int remaining     = budget - total_spent;
    double avg_rating = result.selected.empty() ? 0.0
                      : (double)result.total_rating / result.selected.size();
    RoleCount rc      = check_team_balance(result.selected);

    // Results header
    cout << "\n" << BOLD << CYAN;
    print_line('=');
    cout << "   [OK]  YOUR SELECTED TEAM\n";
    print_line('=');
    cout << RST << "\n";

    cout << "  " << bold("Players Selected") << " : " << green(to_string(result.selected.size())) << " / 11\n";
    cout << "  " << bold("Total Spent     ") << " : " << yellow("Rs." + to_string(total_spent) + " Crores") << "\n";
    cout << "  " << bold("Remaining Budget") << " : " << cyan("Rs." + to_string(remaining) + " Crores") << "\n";
    cout << "  " << bold("Total Rating    ") << " : " << purple(to_string(result.total_rating)) << "\n";
    char avg_buf[8]; sprintf(avg_buf, "%.1f", avg_rating);
    cout << "  " << bold("Average Rating  ") << " : " << green(avg_buf) << "\n";
    cout << "\n  Budget Used : " << progress_bar(total_spent, budget) << "\n";

    // Team Composition
    cout << "\n  " << bold("Team Composition:") << "\n";
    cout << "  Batsmen      : " << cyan(to_string(rc.batsmen))     << "\n";
    cout << "  All-Rounders : " << cyan(to_string(rc.allrounders)) << "\n";
    cout << "  Wkt Keepers  : " << cyan(to_string(rc.keepers))     << "\n";
    cout << "  Bowlers      : " << cyan(to_string(rc.bowlers))     << "\n";

    bool balanced = true;
    if (rc.batsmen < 3) { cout << "  " << yellow("WARNING: Need at least 3 batsmen.\n");       balanced = false; }
    if (rc.keepers < 1) { cout << "  " << yellow("WARNING: Need at least 1 wicket keeper.\n"); balanced = false; }
    if (rc.bowlers < 4) { cout << "  " << yellow("WARNING: Need at least 4 bowlers.\n");       balanced = false; }
    if (balanced)
        cout << "\n  " << green("[OK] Balanced Team -- All role requirements met!") << "\n";

    // Selected players table
    print_section("[OK] SELECTED PLAYERS (PLAYING XI)");
    print_player_table(result.selected, true);

    // Not selected
    if (!result.not_selected.empty()) {
        print_section("[X] NOT SELECTED (BUDGET / LIMIT REACHED)");
        int show = min((int)result.not_selected.size(), 8);
        vector<Player> subset(result.not_selected.begin(), result.not_selected.begin() + show);
        print_player_table(subset, false);
    }

    // Greedy suggestion
    print_section("[IDEA] GREEDY SUGGESTION");
    cout << "  " << yellow(greedy_suggestion(result.not_selected, remaining)) << "\n";

    // Algorithm info
    print_section("[CHART] ALGORITHM INFO");
    cout << "  Algorithm        : " << cyan("0/1 Knapsack -- Dynamic Programming") << "\n";
    cout << "  Time Complexity  : " << dim("O(n x W) = O(" + to_string(players.size()) + " x " + to_string(budget) + ")") << "\n";
    cout << "  Space Complexity : " << dim("O(n x W) = O(" + to_string(players.size()) + " x " + to_string(budget) + ")") << "\n";
    cout << "  Players Pool     : " << dim(to_string(players.size())) << "\n";
    cout << "  Budget (W)       : " << dim("Rs." + to_string(budget) + " Crores") << "\n";

    cout << "\n" << BOLD << CYAN;
    print_line('=');
    cout << "   [TROPHY]  Team Selected! Push to GitHub & Submit!\n";
    print_line('=');
    cout << RST << "\n";

    return 0;
}