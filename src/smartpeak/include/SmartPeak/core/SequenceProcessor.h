// TODO: Add copyright

#pragma once

#include <SmartPeak/core/Filenames.h>
#include <SmartPeak/core/RawDataProcessor.h>
#include <SmartPeak/core/SequenceHandler.h>
#include <SmartPeak/core/SequenceSegmentProcessor.h>
#include <map>
#include <memory> // shared_ptr
#include <set>
#include <string>
#include <vector>

namespace SmartPeak
{
  struct SequenceProcessor {
    SequenceProcessor(SequenceHandler& sh) : sequenceHandler_IO(&sh) {}
    virtual ~SequenceProcessor() = default;

    virtual void process() const = 0;

    SequenceHandler* sequenceHandler_IO = nullptr; /// Sequence handler, used by all SequenceProcessor derived classes
  };

  /**
    Create a new sequence from files or wizard
  */
  struct CreateSequence : SequenceProcessor {
    Filenames        filenames;                    /// Pathnames to load
    std::string      delimiter          = ",";     /// String delimiter of the imported file
    bool             checkConsistency   = true;    /// Check consistency of data contained in files

    CreateSequence() = default;
    CreateSequence(SequenceHandler& sh) : SequenceProcessor(sh) {}
    void process() const override;
  };

  /**
    Apply a processing workflow to all injections in a sequence
  */
  struct ProcessSequence : SequenceProcessor {
    std::map<std::string, Filenames>               filenames;                     /// Mapping from injection names to pathnames
    std::set<std::string>                          injection_names;               /// Injections to select from the sequence (all if empty)
    std::vector<std::shared_ptr<RawDataProcessor>> raw_data_processing_methods_I; /// Events to process

    ProcessSequence() = default;
    ProcessSequence(SequenceHandler& sh) : SequenceProcessor(sh) {}
    void process() const override;
  };

  /**
    Apply a processing workflow to all injections in a sequence segment
  */
  struct ProcessSequenceSegments : SequenceProcessor {
    std::map<std::string, Filenames>                       filenames;                             /// Mapping from sequence groups names to pathnames
    std::set<std::string>                                  sequence_segment_names;                /// Sequence groups to select from the sequence (all if empty)
    std::vector<std::shared_ptr<SequenceSegmentProcessor>> sequence_segment_processing_methods_I; /// Events to process

    ProcessSequenceSegments() = default;
    ProcessSequenceSegments(SequenceHandler& sh) : SequenceProcessor(sh) {}
    void process() const override;
  };
}
