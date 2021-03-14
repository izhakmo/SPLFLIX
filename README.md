# SPLFlix

A C++ Program that simulates "NetFlix" application shell.
SPLFlix offers 2 types of content – movies and tv-series.
After finishing an episode, the program will offer to watch the next episode if such exists.


### Recommendation algorithms

The program has 3 content recommendation algorithms:
  - **Length Recommender** – This algorithm is based on the assumption that users prefer to watch content in a similar length.
  - **Rerun Recommender** – This algorithm is intended for users who don't like new stuff. It will recommend content based on this user's watching history.
  - **Similar Genre** – This algorithm will recommend content based on the most popular tag in the user's watch history.

## Functionality

When starting SPLFLIX, the program will print a message "SPLFLIX is now on" and accepts any of the next input:
- **Create User**
    - Syntax: createuser <user_name> <recommendation_algorithm>, Where the recommendation_algorithm as follows:
        - gen - genere.
        - len - length.
        - rer - rewatch.
- **Change User**
  - Syntax: changeuser <user_name>
- **Delete User**
  - Syntax: deleteuser <user_name>
- **Duplicate User** – create a new user with <new_user_name>, and copys the watch history and the recommendation algorithm from <original_user_name> profile.
  - Syntax: dupuser <original_user_name> <new_user_name>
- **Print Content List** – Prints all the watchable content available.
  - Syntax: content
- **Print Watch History** – Prints the watch history of the current active user.
  - Syntax: watchhist
- **Watch** – Watche <content_id>, where <content_id> is the number of the content in the config file.
  - Syntax: watch <content_id>
- **Print Actions Log** – Prints all the actions that were performed by all users (Excluding current log action), from last to first.
  - Syntax: log
- **Exit** – Exits SPLFlix.
  - Syntax: exit
