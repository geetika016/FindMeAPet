# FindMeAPet

## Purpose:
Application designed to facilitate Pet adoption from Animal Shelters, which generates an optimal client-pet matching based on their attributes and preferences quantified using weights.

## Operation:
The application allows Animal Shelter Staff to create Profiles for Pets available for adoption. The profile has a range of attributes, physical as well as non-physical that apply to the Animal.
Clients can create their own profiles by specifying their preferences as well as personal and work-life details relevant to pet adoption. They can preview the list of available Pets for adoption and specify preferences as well.
The Staff can run Matching Algorithm to obtain the set of optimal matches based on the current Clients and Pets in the database.

## Matching Methodology:
The Application uses weighted scores to calculate scores for both clients and pets. The system is optimized to always give animal preferences priority over clients so as to ensure that the animal is always matched to the best client option. The scoring matrix has a cutoff threshold of 1.36 to ensure the quality of matches.


## Compilation and Launch Instructions:
- Execute run.sh with the command ./run.sh
  - If this does not work, execute the command "chmod +x run.sh" to give execute permissions to the file
- When run.sh is executed, it builds and runs cuACS
  - After executing run.sh the first time, you may execute the command ./cuACS in the future to run the program.
- To login to the system as a staff member, enter "matilda23" into the **username** field and "matilda23" into the **password** field and click **login**.
- To login to the system as a client, enter "Joe" into the **username** field and "joe" into the **password** field and click **login**.
