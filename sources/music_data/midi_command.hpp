#pragma once

#include "aliases.hpp"
#include "midi_context.hpp"

#include <variant>

namespace midi_command{

    struct QueuedNoteOn{
        units::midi::Channel channel;
        units::midi::Note note;
        units::midi::Velocity velocity;
    };

    struct QueuedNoteOff{
        units::midi::Channel channel;
        units::midi::Note note;
    };

    using Command = std::variant<
        QueuedNoteOn, 
        QueuedNoteOff
    >;

    void execute(const Command &command, ExecutionContext &context);

    // // namespace _{
    // class BaseCommand{
    // public:
    //     BaseCommand() = default;
    //     virtual ~BaseCommand() = 0;

    //     virtual void execute(ExecutionContext &context) = 0;
    // };
    // // } // namespace _



    // class NoteOn : public BaseCommand{
    // private:
    //     const units::midi::Channel    channel_;
    //     const units::midi::Note       note_;
    //     // units::midi::Velocity   velocity_;

    // public:
    //     NoteOn(const units::midi::Channel channel, const units::midi::Note note)
    //         : channel_{channel}, note_{note}{}
    //     NoteOn() = delete;
    //     ~NoteOn() override = default;

    //     void execute(ExecutionContext &context) override;
    // };

    // class NoteOff : public BaseCommand{
    // private:
    //     const units::midi::Channel    channel_;
    //     const units::midi::Note       note_;

    // public:
    //     NoteOff(const units::midi::Channel channel, const units::midi::Note note)
    //         : channel_{channel}, note_{note}{}
    //     NoteOff() = delete;
    //     ~NoteOff() override = default;

    //     void execute(ExecutionContext &context) override;
    // };

} // namespace midi_command