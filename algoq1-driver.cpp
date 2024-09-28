#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>

struct Hospital {
    int remainingSlots = 2;
    char id;
    std::vector<char> prefList;
    
};
struct Student {
    bool engaged = false;
    int id;
    std::vector<char> prefList;
    std::vector<char> notProposedTo;
    char assignedTo;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
       std::cout << "Usage: ./algoq1.out input-text-file" << std::endl;
       return 0;
    }
    std::ifstream ifs{ argv[1] };
    if (!ifs) { // file opened? NO - then abort program
       std::cerr << "Cannot open input file \"" << argv[1] << "\"" << std::endl;
       return 0;
    }

    std::vector<Hospital> hVector;
    std::string fullHospitalData;
    std::getline(ifs, fullHospitalData);

    std::istringstream dataStream (fullHospitalData);
    // Read the first line containing hospital data
    
    //Proof the damn daata is actually going into hospitalData
    /*std::getline(ifs, fullHospitalData);
    std::cout << std::endl << fullHospitalData << std::endl;
    if (std::getline(ifs, fullHospitalData)) {
        std::cout << "Data read from file: " << fullHospitalData << std::endl;
    } else {
        std::cerr << "Failed to read data from the file." << std::endl;
        return 1; // Exit if reading failed
    }
    */
    
    
    //iss only contains the very first line containing all the data from the hospitals
    //each iteration only has data from one hospital
    std::string currentHospitalData;
    while (std::getline(dataStream, currentHospitalData, ';')) {
        if(currentHospitalData.empty() || currentHospitalData.size() < 3)continue;
        // std::cout << currentHospitalData.size();
        // std::cout << currentHospitalData << std::endl;
        
        // Create a new hospital object
        Hospital currentHospital;   
        //Use current position      
        size_t currentPosition;
        
        currentPosition = currentHospitalData.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        //std::cout <<  std::endl << currentPosition;
        //std:cout << std::endl
        // Extract the ID, uses currentPosition in case in some freak accident the thing isnt the first character
        currentHospital.id = currentHospitalData[currentPosition];
        
        while (currentHospitalData.find_first_of("123456789", currentPosition) != std::string::npos)
        {
            currentPosition = currentHospitalData.find_first_of("123456789", currentPosition);
            currentHospital.prefList.push_back((currentHospitalData[currentPosition]));
            currentPosition++;
        }
        // Add the populated hospital object to the vector
        hVector.push_back(currentHospital);
        
    }
    
    for (const auto& hospital : hVector) {
        std::cout << "Hospital ID: " << hospital.id << "\n";
        std::cout << "Remaining Slots: " << hospital.remainingSlots << "\n";
        std::cout << "Preference List: ";
        for (char pref : hospital.prefList) {
            std::cout << pref << " ";
        }
        std::cout << "\n";
    }



    // //THIS WILL BE DONE BY TEXT INPUT
    // Hospital C;
    // C.id = 'C';
    // C.prefList.push_back(5);
    // C.prefList.push_back(1);
    // C.prefList.push_back(2);
    // C.prefList.push_back(4);
    // C.prefList.push_back(3);

   

    // C.remainingSlots = 2;

    // Hospital M;
    // M.id = 'M';
    // M.prefList.push_back(5);
    // M.prefList.push_back(3);
    // M.prefList.push_back(1);
    // M.prefList.push_back(2);
    // M.prefList.push_back(4);

    // M.remainingSlots = 2;

    

    // hVector.push_back(M);
    // hVector.push_back(C);

    // std::vector<Student> sVector;
    // for (int i = 1; i < 6; i++) {
    //     Student s;
    //     s.id = i;
    //     s.engaged = false;
    //     if (i < 4) {
    //         s.prefList.push_back('C');
    //         s.prefList.push_back('M');
    //     }
    //     else {
    //         s.prefList.push_back('M');
    //         s.prefList.push_back('C');
    //     }
    //     s.notProposedTo = s.prefList;
    //     sVector.push_back(s);
    // }

    // //THIS WILL BE DONE BY TEXT INPUT
    // std::vector<Student>::iterator currentStudent = sVector.begin();

    std::vector<Student> sVector;
    std::string fullStudentData;
    std::getline(ifs, fullStudentData);

    std::istringstream studentStream (fullStudentData);
    // Read the first line containing hospital data
    
    //iss only contains the very first line containing all the data from the hospitals
    //each iteration only has data from one hospital
    std::string currentStudentData;

    // //Proof the damn daata is actually going into studentData
    // std::getline(ifs, fullStudentData);
    // std::cout << std::endl << fullHospitalData << std::endl;

    

    while (std::getline(studentStream, currentStudentData, ';')) {
        if(currentStudentData.empty() || currentStudentData.size() < 3)continue;
        // std::cout << currentHospitalData.size();
        // std::cout << currentHospitalData << std::endl;
        
        // Create a new hospital object
        Student currentStudent;   
        //Use current position      
        size_t currentPosition;
        
        currentPosition = currentStudentData.find_first_of("123456789");
        //std::cout <<  std::endl << currentPosition;
        //std:cout << std::endl
        // Extract the ID, uses currentPosition in case in some freak accident the thing isnt the first character
        currentStudent.id = currentStudentData[currentPosition] - '0';
        
        while (currentStudentData.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ", currentPosition) != std::string::npos)
        {
            currentPosition = currentStudentData.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ", currentPosition);
            currentStudent.prefList.push_back((currentStudentData[currentPosition]));
            currentStudent.notProposedTo = currentStudent.prefList;
            currentPosition++;
        }
        // Add the populated hospital object to the vector
        sVector.push_back(currentStudent);
        
    }

    for (const auto& student : sVector) {
        std::cout << "Student: " << student.id << "\n";
        std::cout << "Preference List: ";
        for (char pref : student.prefList) {
            std::cout << pref << " ";
        }
        std::cout << "\n";
    }


//The algo part

    std::vector<Student>::iterator currentStudent = sVector.begin();
    //HOSPITALS ARE MEN
    while (true) {
            
        if (currentStudent->engaged == false && currentStudent->notProposedTo.size() > 0) {
            for (long unsigned int i = 0; i < currentStudent->notProposedTo.size(); i++) {
                char id = currentStudent->notProposedTo[i];
                std::vector<Hospital>::iterator hospital = std::find_if(hVector.begin(), hVector.end(), [id](Hospital h) {
                    return h.id == id;
                    });
                std::vector<Student>::iterator student = std::find_if(sVector.begin(), sVector.end(),
                    [currentStudent](Student s) {
                    return s.id ==  currentStudent->id;
                    });
                if (hospital->remainingSlots > 0) {
                    student->engaged = true;
                    student->assignedTo = id;
                    hospital->remainingSlots--;
                    currentStudent->notProposedTo.erase(currentStudent->notProposedTo.begin() + i);
                    break;
                }
                else {
                    //currently engaged
                    // if the hospital prefers this student
                   


                }
            }

        }

        std::vector<Student>::iterator freeStudent = std::find_if(sVector.begin(), sVector.end(), [](Student s) {
            return s.engaged == false && s.notProposedTo.size() > 0;
            });
        if (freeStudent != sVector.end()) {
            currentStudent = freeStudent;
        }
        else {
            break;
        }
    }

    return 0;
}