/*
 * config.h
 *
 *  Created on: May 5, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/*
 * This is the maixmum value that simulation time is able to have. 
 */
#define SIMULATION_END_TIME 1000.0
/*
 * This is the step which simulation time advances with each iteration.
 * Simulation time starts with 0 and goes to SIMULATION_END_TIME.
 */
#define SIMULATION_STEP 0.1

/*
 * Current version simulates a road while cars are moving in both direction.
 * This is the road length.
 */
#define ROAD_LENGTH 10000.0
/*
 * There are some Access Points in the simulating road. This is the distance
 * between two of them.
 */
#define INTER_ACCESS_POINT_DISTANCE 3000.0
/*
 * Each Access Point has a working range which is a circle centered right at
 * the Access Point itself. This is the diameter of the range circle arounf
 * the Access Point.
 */
#define ACCESS_POINT_DIAMETER 3000.0

/*
 * Number of all channels in the simulation.
 */
#define NUMBER_OF_CHANNELS 200

/*
 * Number of watchers which they are visiting a certain channel ???????.
 */
#define MAX_WATCHERS_PER_CHANNEL 40

/*
 * Interval which an access point uses to send WHO_NEEDS_CHANNEL broadcast
 * message periodically.
 */
#define ACCESS_POINT_WHO_NEEDS_CHANNEL_BROADCAST_MESSAGE_INTERVAL 50
/*
 * Trace files are simulation inputs. They contain the order of enterances
 * for cars. Each simulation consumes one trace file for each lane in the road 
 * e.g a simulation with a road containing 6 lanes, will use 6 trace files. This
 * option is the maximum allowed trace files to be used. 0 means infinity
 * and all of the trace files in the directory specified by TRACE_FILES_PATH
 * configuration variable will be consumed. If we have 182 trace files and
 * the road has 6 lanes, each simulation consumes 6 trace files. If we set 0
 * for this option we will have 30 simulation instances and last 2 trace files 
 * are useless.
 */
#define MAX_TRACE_FILES 0   

/*
 * Directory which all trace files are placed in it.
 */
#define TRACE_FILES_PATH "/home/kamran/data/prj/pour-moi/myprjs/ind/momeni/old-files/trace"
// #define TRACE_FILES_PATH "D:\\pour-moi\\myprjs\\ind\\momeni\\old-files\\trace"

/*
 * OUTER_LANE_SPEED: Used when simulating road contains 6 lanes. This is the
 * speed of cars moving in the outer lane (less speed). Unit is meter/second.
 * 
 * OUTER_LANE_MINIMUM_DISTANCE: Used when simulating road contains 6 lanes.
 * This is the minimum allowed speed in the outer lane.
 *
 * OUTER_LANE_AVERAGE_DISTANCE: Used when simulating road contains 6 lanes.
 * This is the average speed which a car moves with in the outer lane.
 *
 * OUTER_LANE_MAXIMUM_DISTANCE: Used when simulating road contains 6 lanes.
 * This is the maximum allowed speed in the outer lane.
 */
#define OUTER_LANE_SPEED (90.0 / 3.6)
#define OUTER_LANE_MINIMUM_DISTANCE 10.0
#define OUTER_LANE_AVERAGE_DISTANCE 20.0
#define OUTER_LANE_MAXIMUM_DISTANCE 30.0

/*
 * These options are similar to those in previous sections, designed for outer
 * lane while simulating a road with 6 lanes.
 */
#define MIDDLE_LANE_SPEED (120.0 / 3.6)
#define MIDDLE_LANE_MINIMUM_DISTANCE 15.0
#define MIDDLE_LANE_AVERAGE_DISTANCE 25.0
#define MIDDLE_LANE_MAXIMUM_DISTANCE 35.0

/*
 * These options are similar to those in previous sections, designed for outer
 * lane while simulating a road with 6 lanes.
 */
#define INNER_LANE_SPEED (150.0 / 3.6)
#define INNER_LANE_MINIMUM_DISTANCE 20.0
#define INNER_LANE_AVERAGE_DISTANCE 70.0
#define INNER_LANE_MAXIMUM_DISTANCE 100.0

/*
 * Initial seed for srand() function.
 */
#define SRAND_INITIAL_MAPPING 23
/*
 * A certain mathematical constant used in ZIPF distribution. ZIPF distribution
 * is used for simulating requests for channels made by moving cars.
 */
#define ZIPF_ALPHA 1.3

/*
 * Log all handover messages. (0 disable, 1 enable)
 */
#define VERBOSE_HANDOVER 0
/*
 * Log all car movings.(0 disable, 1 enable)
 */
#define VERBOSE_MOVE 0
/*
 * Log all car generations. (0 disable, 1 enable)
 */
#define VERBOSE_GENERATE_CAR 0
/*
 * Log when a car exits the road. (0 disable, 1 enable)
 */
#define VERBOSE_EXIT_CAR 0
/*
 * Log when a car joins a channel. (0 disable, 1 enable)
 */
#define VERBOSE_JOIN_CHANNEL 0
/*
 * Log when a car leaves a channel. (0 disable, 1 enable)
 */
#define VERBOSE_LEAVE_CHANNEL 0
/*
 * Log when a WHO_NEEDS_CHANNEL message is broadcasted. (0 disable, 1 enable)
 */
#define VERBOSE_WHO_NEEDS_CHANNEL 0
/*
 * Log when a I_STILL_NEED_CHANNEL message is transmitted. (0 disable, 1 enable)
 */
#define VERBOSE_I_STILL_NEED_CHANNEL 0

#define MUTE 1 || (!VERBOSE_HANDOVER && !VERBOSE_MOVE && !VERBOSE_GENERATE_CAR && !VERBOSE_EXIT_CAR && !VERBOSE_JOIN_CHANNEL && !VERBOSE_LEAVE_CHANNEL && !VERBOSE_WHO_NEEDS_CHANNEL && !VERBOSE_I_STILL_NEED_CHANNEL)

/*
 * Produce a JSON based report that includes all the details about a simulation.
 * (0 disable, 1 enable)
 */
#define PRODUCE_SIMULATION_JSON 0
/*
 * Produce a summary file for each simulation. This file includes all nessecary
 * variables and their final calculated values in a simple format.
 * (0 disable, 1 enable)
 */
#define PRODUCE_RESULT_FILE 1
/*
 * The path which all reports goes in.
 */
#define OUTPUT_DIRECTORY "/home/kamran/"
// #define OUTPUT_DIRECTORY "d:"

#endif /* CONFIG_H_ */
