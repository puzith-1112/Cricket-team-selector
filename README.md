# Cricket-team-selector
Title: IPL Cricket Team Selection Using 0/1 Knapsack Dynamic Programming and Greedy Algorithm
Cricket-team-selector
Title: IPL Cricket Team Selection Using 0/1 Knapsack Dynamic Programming and Greedy Algorithm

🏏 IPL Cricket Team Selector
Optimal Playing XI Selection Using 0/1 Knapsack Dynamic Programming + Greedy Algorithm
📌 Overview
This project simulates an IPL-style cricket auction system that intelligently selects the best Playing XI from a pool of 28 international players within a user-defined budget. It combines Dynamic Programming (0/1 Knapsack) for optimal selection and a Greedy Algorithm for efficiency-based player suggestions — making it a complete decision-support tool for cricket team management.

🎯 Problem Statement
In IPL auctions, team owners must:

Select exactly 11 players from a large pool
Stay within a fixed budget (in Crores)
Maintain proper team balance (batsmen, bowlers, all-rounders, wicket keepers)
Maximize overall team rating
Selecting the optimal combination manually from hundreds of players is computationally infeasible — making this a classic combinatorial optimization problem.

🧠 Algorithms Used
1. Dynamic Programming — 0/1 Knapsack (Main Algorithm)
Knapsack Concept	Cricket Mapping
Item	Player
Weight	Cost (₹ Crores)
Value	Rating (1–100)
Capacity	Budget
The DP table is built bottom-up:

dp[i][w] = best total rating using first i players with budget w
This guarantees the globally optimal team selection.

Time Complexity: O(n × W)
Space Complexity: O(n × W)
where n = number of players, W = budget in Crores

2. Greedy Algorithm (Supporting Role)
Used to suggest the best unselected player based on efficiency:

Efficiency = Rating / Cost
Greedy gives a quick recommendation but does not guarantee a globally optimal solution — which is why DP handles the final selection.

⚙️ How It Works
Step 1 → Display full player pool (28 players)
Step 2 → User enters auction budget
Step 3 → Mandatory role picks (Greedy by highest rating)
           └── 3 Batsmen
           └── 1 Wicket Keeper
           └── 2 All-Rounders
           └── 4 Bowlers
Step 4 → DP Knapsack fills remaining slots within leftover budget
Step 5 → Backtrack DP table to identify selected players
Step 6 → Team balance validation
Step 7 → Greedy suggestion for best remaining player
Step 8 → Display results with budget progress bar
👥 Player Pool
The database includes 28 international players across 4 roles:

Role	Players
Batsman	Virat Kohli, Rohit Sharma, Babar Azam, David Warner, and more
All-Rounder	Ben Stokes, Ravindra Jadeja, Hardik Pandya, and more
Wicket Keeper	MS Dhoni, Jos Buttler, Rishabh Pant, and more
Bowler	Jasprit Bumrah, Pat Cummins, Mitchell Starc, and more
Each player has: Name, Cost (Cr), Rating, Role, Country, Bat, Bowl, Field stats.

🖥️ Sample Output
================================================================
   [CRICKET]  CRICKET TEAM SELECTOR  [TROPHY]
   IPL-Style Auction -- DP Knapsack Algorithm
================================================================

-- SELECTED PLAYERS (PLAYING XI) ------------------------------
  #   Name                 Role           Country       Cost    Rating
  1   Virat Kohli          [BAT] Batsman  India         Rs.15Cr   95
  2   Rohit Sharma         [BAT] Batsman  India         Rs.14Cr   92
  3   Babar Azam           [BAT] Batsman  Pakistan      Rs.13Cr   90
  4   MS Dhoni             [WK]  Wkt Keep India         Rs.12Cr   91
  5   Ben Stokes           [AR]  All-Roun England       Rs.14Cr   93
  6   Ravindra Jadeja      [AR]  All-Roun India         Rs.12Cr   89
  7   Jasprit Bumrah       [BWL] Bowler   India         Rs.14Cr   95
  8   Pat Cummins          [BWL] Bowler   Australia     Rs.13Cr   92
  9   Mitchell Starc       [BWL] Bowler   Australia     Rs.11Cr   88
  10  Kagiso Rabada        [BWL] Bowler   S. Africa     Rs.10Cr   87
  11  Ravichandran Ashwin  [BWL] Bowler   India         Rs.10Cr   86

Budget Used: [############################..........] 76.7%
[OK] Balanced Team -- All role requirements met!
🚀 How to Run
Prerequisites
g++ compiler with C++17 support
Compile
g++ -o cricket_selector cricket_selector.cpp -std=c++17
Run
./cricket_selector
Input
Enter total auction budget (Rs. Crores, e.g. 90): 120
Recommended budget: 110–130 Crores for a full 11-player team.

📁 Project Structure
cricket-team-selector/
│
├── cricket_selector.cpp     # Main source file
└── README.md                # Project documentation
💡 Key Design Decisions
Why not pure Greedy? Greedy picks the locally best player (highest rating/cost ratio) but can miss the globally optimal combination. For example, two mid-rated players may together provide more value than one expensive star within the same budget.

Why 0/1 Knapsack? Each player can only be selected once (0 or 1 times), and we need the globally optimal combination — exactly what 0/1 Knapsack DP solves.

Why Hybrid (DP + Greedy)?

DP handles optimal final selection
Greedy handles quick suggestions and mandatory picks
This hybrid approach gives both correctness and speed.

📊 Complexity Analysis
Metric	Value
Time Complexity	O(n × W)
Space Complexity	O(n × W)
Players (n)	28
Budget range (W)	80–150 Cr (recommended)
🏆 Features
✅ IPL-style auction simulation
✅ 0/1 Knapsack DP for optimal selection
✅ Role-based mandatory picks
✅ Greedy efficiency-based suggestion
✅ Team balance validation
✅ Colored terminal output
✅ Budget progress bar
✅ Not-selected players list with reasons
👨‍💻 Author
Billuri Hari Bhanu Teja B.Tech Computer Science Engineering SRM University AP

📝 Note for Viva
"This project uses the 0/1 Knapsack Dynamic Programming algorithm to select the optimal Playing XI within a budget while maximizing team rating. A Greedy algorithm supports the system by suggesting the best remaining player based on rating-to-cost efficiency ratio. The hybrid approach ensures both optimality and practical decision support."
