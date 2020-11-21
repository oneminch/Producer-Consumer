#if !defined HIGH_PERFORMANCE_COUNTER
#define HIGH_PERFORMANCE_COUNTER

namespace CSC1310
{
class HighPerformanceCounter
{
   private:
      double micro_spt;  //micro_seconds per tick

      HighPerformanceCounter();
      static HighPerformanceCounter* hpc;
      static int getTicksPerSecond();

   public:
      virtual ~HighPerformanceCounter();

      static HighPerformanceCounter* getHighPerformanceCounter();
      int getCurrentTimeInTicks();
      double getTimeDifferenceInMicroSeconds(int start_time, int end_time);
};
}

#endif
