/*
 * enums.h
 *
 *  Created on: Apr 10, 2014
 *      Author: Kamran Amini <kam.cpp@gmail.com>
 */

#ifndef ENUMS_H_
#define ENUMS_H_

enum LaneDirection {
  LaneDirection_None,
  LaneDirection_LeftToRight,
  LaneDirection_RightToLeft
};

enum TimeUnit {
  TimeStepUnit_None,
  TimeStepUnit_Millisecond,
  TimeStepUnit_DeciSecond,
  TimeStepUnit_Second
};

enum CarStoryEventStatus {
  CarStoryEventStatus_None,
  // CarStoryEventStatus_RequestForChannel,
  // CarStoryEventStatus_StartWatchingChannel,
  // CarStoryEventStatus_TerminateChannel
  CarStoryEventStatus_Viewing,
  CarStoryEventStatus_Zapping
};

enum PreserveChannelBeforeHandoverProtocolCommandType {
  PreserveChannelBeforeHandoverProtocolCommandType_None,
  PreserveChannelBeforeHandoverProtocolCommandType_Join,
  PreserveChannelBeforeHandoverProtocolCommandType_JoinAccepted,
  PreserveChannelBeforeHandoverProtocolCommandType_JoinRejected,
  PreserveChannelBeforeHandoverProtocolCommandType_Leave,
  PreserveChannelBeforeHandoverProtocolCommandType_LeaveAccepted,
  PreserveChannelBeforeHandoverProtocolCommandType_LeaveRejected,
  PreserveChannelBeforeHandoverProtocolCommandType_BroadcastData,
  PreserveChannelBeforeHandoverProtocolCommandType_IStillNeedTheChannel,
  PreserveChannelBeforeHandoverProtocolCommandType_WhoNeedsTheChannel,
  PreserveChannelBeforeHandoverProtocolCommandType_PreserveChannel,
  PreserveChannelBeforeHandoverProtocolCommandType_PreserveChannelAccepted,
  PreserveChannelBeforeHandoverProtocolCommandType_PreserveChannelRejected,
  PreserveChannelBeforeHandoverProtocolCommandType_CancelReservation,
  PreserveChannelBeforeHandoverProtocolCommandType_CancelReservationAccepted,
  PreserveChannelBeforeHandoverProtocolCommandType_CancelReservationRejected,
  PreserveChannelBeforeHandoverProtocolCommandType_ChangeReservation,
  PreserveChannelBeforeHandoverProtocolCommandType_ChangeReservationAccepted,
  PreserveChannelBeforeHandoverProtocolCommandType_ChangeReservationRejected
};

enum UnderlyingNegotationCommandType {
  UnderlyingNegotationCommandType_None,
  UnderlyingNegotationCommandType_Hello,
  UnderlyingNegotationCommandType_Bye
};

enum SimulationExceptionType {
  SimulationExceptionType_None,
  SimulationExceptionType_NoCoveringAccessPoint,
  SimulationExceptionType_NetworkDeviceNotFound,
  SimulationExceptionType_NotSupportedCommand,
  SimulationExceptionType_NotSupportedPcbhProtocolCommand
};

enum ChannelStateType {
  ChannelStateType_None = -1000,
  ChannelStateType_NotBroadcasted = -2,
  ChannelStateType_PreservedAndBroadcasted = -1,
  ChannelStateType_NotPreservedAndBroadcasted = 0,
  ChannelStateType_Broadcasted
};

#endif /* ENUMS_H_ */
