#pragma once

#include <cstddef>
#include <hardware/uart.h>

#include "aliases.hpp"

namespace constants{

    namespace pins{
        constexpr physical::Pin MotorDirection {15};
        constexpr physical::Pin MotorStep      {14};
        constexpr physical::Pin MotorEnable    {13};

        constexpr physical::Pin MuxData  {4};
        constexpr physical::Pin MuxClock {5};

        constexpr physical::Pin MidiTransmit {0};
        constexpr physical::Pin MidiReceive  {1};

        constexpr physical::Pin LightAnalogOut {26};
    } // namespace pins

    namespace adc{
        constexpr physical::Channel LightInputChannel{0};
    } // namespace adc

    namespace i2c{
        constexpr uint32_t Frequency{100000}; // 100 kHz
    } // namespace i2c

    namespace i2c_address{
        constexpr physical::I2CAddress MuxFront  {0x70};
        constexpr physical::I2CAddress MuxBack   {0x71};
        constexpr physical::I2CAddress ColorSensor{0x29};
    } // namespace i2c_address

    namespace color_sensor{
        // command bit (0x80) + auto increment bit (0x20)
        constexpr physical::Register CommandBit{0xa0};

        constexpr physical::Register Enable           {0x00 | CommandBit};
        constexpr physical::Register IntegrationTime  {0x01 | CommandBit};
        constexpr physical::Register Control          {0x0f | CommandBit};
        constexpr physical::Register Id               {0x12 | CommandBit};
        constexpr physical::Register ClearDataLow     {0x14 | CommandBit};

        // configuration
        constexpr uint8_t TotalSensorCount      {16};
        constexpr uint8_t SensorsPerMux         {8};
        constexpr uint8_t EnableValue           {0x03}; // PON (bit 0) and AEN (bit 1)
        constexpr uint8_t IntegrationTimeValue  {0xf6}; // ~24ms
        constexpr uint8_t GainValue             {0x01}; // 4x gain
        constexpr uint8_t RgbcDataByteCount     {8};

        // delay
        constexpr units::Us MinimumReadInterval{50000};

        // mux
        constexpr uint8_t MuxDisableMask{0x00};

        // color threshold
        constexpr uint16_t BlackClearThreshold      {200};
        constexpr float WhiteSaturationThreshold    {.25f};
        constexpr float YellowRedRatioThreshold     {1.5f};
        constexpr float YellowGreenRatioThreshold   {1.5f};

        // others
        constexpr int FrontToBackDistance{5};
    } // namespace color_sensor

    namespace motor{
        constexpr bool ForwardDirection{1};
        constexpr units::Us MaxStepInterval{800};
        constexpr units::Us AccelerationStep{10};

        constexpr uint8_t DefaltStepRate{4};
    } // namespace motor

    namespace light_sensor{
        constexpr units::Percentage NoPaperThreshold{.9f};
        constexpr units::Percentage WhiteThreshold{.8f}; // above
        constexpr units::Percentage BlackThreshold{.3f}; // below

    } // namespace light_sensor

    namespace midi{
        // UART configuration
        inline uart_inst_t *UartInstance{uart0};
        constexpr uint32_t BaudRate     {31250};
        constexpr uint8_t DataBits      {8};
        constexpr uint8_t StopBits      {1};

        // message status bytes
        constexpr uint8_t NoteOffStatus         {0x80};
        constexpr uint8_t NoteOnStatus          {0x90};
        constexpr uint8_t ProgramChangeStatus   {0xc0};
        constexpr uint8_t ControlChangeStatus   {0xb0};

        // message parameters
        constexpr uint8_t ChannelMask           {0x0f};
        constexpr uint8_t MaximumVelocity       {127};
        constexpr uint8_t MaximumNote           {127};
        constexpr uint8_t MaximumChannel        {15};

        // controller
        constexpr uint8_t BankSelectController  {0};
        constexpr uint8_t AllSoundOffController {120};
        constexpr uint8_t ControllerValueOff    {0};

        // MT-32 sound variation
        constexpr uint8_t DefaultBankValue      {0};
        constexpr uint8_t AlternativeBankValue  {127};
    } // namespace midi

    namespace system{
        constexpr uint16_t MaxAdcValue{4095}; // 12 bits
    } // namespace system

} // namespace constants