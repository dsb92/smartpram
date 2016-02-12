/*************BESKRIVELSE AF KLASSE************/
/* ManualController er en kontrolklasse, der står for den manuelle styring af Vugge og Uro.
 * Denne klasse skal blot sende start og stop beskeder til Vugge og Uro forspurgt af UIController.
 */

#ifndef MANUALCONTROLLER_H_
#define MANUALCONTROLLER_H_

#include "common.hpp" 

class ManualController : public osapi::ThreadFunctor
{

public:
	ManualController();
	
	enum
	{
		ID_START_CRADLE,	// Besked som ManualController får, når UIController har forspurgt om at starte vugge.
		ID_STOP_CRADLE,		// Besked som ManualController får, når UIController har forspurgt om at stoppe vugge.
		ID_CRADLE_STOPPED,	// Besked som ManualController får, når vugge er stoppet.
		ID_START_MOBILE,	// Besked som ManualController får, når UIController har forspurgt om at starte uro.
		ID_STOP_MOBILE,		// Besked som ManualController får, når UIController har forspurgt om at stoppe uro.	
		ID_MOBILE_STOPPED	// Besked som ManualController får, når uro er stoppet.
	};

	osapi::MsgQueue* getMsgQueue() { return &mq_; }

	void setMqs( osapi::MsgQueue* cradleMq, osapi::MsgQueue* mobileMq, osapi::MsgQueue* UIMq );
private:
	osapi::MsgQueue mq_;
	static const int MAX_QUEUE_SIZE = 10;
	void handleMsg(osapi::Message* msg, unsigned long id);
	bool running_;
	void run();

	osapi::MsgQueue* cradleMq_;
	osapi::MsgQueue* mobileMq_;
	osapi::MsgQueue* UIMq_;

};

#endif