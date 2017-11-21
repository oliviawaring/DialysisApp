/****session.h ****/

struct Session {
   double currentWeight;
   double targetWeight;
   int treatmentTime;
   double ufRate;
   int bpSitting_Pre[2];
   int bpStanding_Pre[2];
   int bpSitting_Post[2];
   int bpStanding_Post[2];
   int pulse_Pre;
   int pulse_Post;
   double temp_Pre;
   double temp_Post;
};

// Somehow, it's going to be a series of sessions that we ultimately integrate with Matlab


