//
// Created by Henning Tandberg on 10/05/2025.
//

#ifndef USB_RUBBER_DUCKY_DUCKY_PACKET_FACTORY_TESTS_H
#define USB_RUBBER_DUCKY_DUCKY_PACKET_FACTORY_TESTS_H

void CommandPacket_Create_PacketContainsProvidedCommand(void);
void CommandPacket_Create_HeaderIndicatesCommandPacket(void);
void CommandPacket_Create_HeaderHasCorrectCommandLen(void);

#endif //USB_RUBBER_DUCKY_DUCKY_PACKET_FACTORY_TESTS_H
