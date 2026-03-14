#include "midi_command.hpp"

#include "midi_context.hpp"
#include "midi_unit/midi_manager.hpp"

using namespace midi_command;


void NoteOn::execute(ExecutionContext &context){
	context.midiManager.noteOn(channel_, note_, 100); // TODO: magic number, default velocity

	if(channel_ < context.state.lastPlayedNotes.size()){
		context.state.lastPlayedNotes[channel_] = note_;
	}


}

void NoteOff::execute(ExecutionContext &context){
	context.midiManager.noteOff(channel_, note_);

	if(channel_ < context.state.lastPlayedNotes.size()){
		context.state.lastPlayedNotes[channel_] = 0;
	}

    
}