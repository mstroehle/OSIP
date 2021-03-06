#ifndef PIPELINESTAGE_IMPL_H
#define PIPELINESTAGE_IMPL_H

#include "pipelinestage.h"

using namespace OSIP;

template<class I, class O>
PipelineStage<I, O>::PipelineStage()
{
    _Inlet = shared_ptr<Inlet<I>>(new Inlet<I>);
}

template<class I, class O>
void PipelineStage<I, O>::connect(shared_ptr<Inlet<O>> inlet)
{
    _Outlets.push_back(inlet);
}

template<class I, class O>
void PipelineStage<I, O>::log(string msg){
    _Log.push_back(msg);
    sig_MessageLogged(msg);
}

template<class I, class O>
void PipelineStage<I, O>::preStage(){
    sig_StageStarted();
}

template<class I, class O>
void PipelineStage<I, O>::postStage(){
    sig_StageFinished();
}

template<class I, class O>
void PipelineStage<I, O>::workStage(){

}

template<class I, class O>
void PipelineStage<I, O>::start(){
    sig_StageFinished();

    stopThread = false;

    preStage();

    _StageThread = thread(&PipelineStage<I,O>::workStage, this);
}

template<class I, class O>
Payload<I> PipelineStage<I, O>::fetchPayload(){
    return _Inlet.get()->readData();
}

template<class I, class O>
void PipelineStage<I, O>::sendPayload(Payload<O> payload){
    if(_Outlets.size() != 0){
        for(shared_ptr<Inlet<O>> o : _Outlets){
            o.get()->writeData(payload);
        }
    }
}

template<class I, class O>
void PipelineStage<I, O>::pipelineSleep(int milli){
    std::this_thread::sleep_for(std::chrono::milliseconds(milli));
}

template<class I, class O>
boost::signals2::signal<void ()>::slot_type PipelineStage<I, O>::slotDAQFinished(){
    m_DAQFinished = true;
    return boost::signals2::signal<void ()>();
}

template<class I, class O>
boost::signals2::signal<void ()>::slot_type PipelineStage<I, O>::slotSavingFinished(){
    m_SavingFinished = true;
    return boost::signals2::signal<void ()>();
}

template<class I, class O>
boost::signals2::signal<void ()>::slot_type PipelineStage<I, O>::slotProcessingFinished(){
    m_ProcessingFinished = true;
    return boost::signals2::signal<void ()>();
}

#endif // PIPELINESTAGE_IMPL_H
