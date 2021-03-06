// --------------------------------------------------------------------------
//   SmartPeak -- Fast and Accurate CE-, GC- and LC-MS(/MS) Data Processing
// --------------------------------------------------------------------------
// Copyright The SmartPeak Team -- Novo Nordisk Foundation 
// Center for Biosustainability, Technical University of Denmark 2018-2021.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Douglas McCloskey $
// $Authors: Douglas McCloskey $
// --------------------------------------------------------------------------

#define BOOST_TEST_MODULE SequenceHandler test suite
#include <boost/test/included/unit_test.hpp>
#include <SmartPeak/core/SequenceHandler.h>
#include <SmartPeak/core/SampleType.h>

using namespace SmartPeak;
using namespace std;

BOOST_AUTO_TEST_SUITE(sequencehandler)

BOOST_AUTO_TEST_CASE(constructor)
{
  SequenceHandler* ptr = nullptr;
  SequenceHandler* nullPointer = nullptr;
  ptr = new SequenceHandler();
  BOOST_CHECK_NE(ptr, nullPointer);
  delete ptr;
}

BOOST_AUTO_TEST_CASE(addSampleToSequence)
{
  MetaDataHandler meta_data1;
  meta_data1.setFilename("file1");
  meta_data1.setSampleName("sample1");
  meta_data1.setSampleGroupName("sample");
  meta_data1.setSequenceSegmentName("sequence_segment1");
  meta_data1.setSampleType(SampleType::Unknown);
  meta_data1.acq_method_name = "6";
  meta_data1.inj_volume = 7.0;
  meta_data1.inj_volume_units = "8";
  meta_data1.batch_name = "9";
  OpenMS::FeatureMap featuremap1;
  featuremap1.setMetaValue("foo1", "bar1");

  MetaDataHandler meta_data2;
  meta_data2.setFilename("file2");
  meta_data2.setSampleName("sample2");
  meta_data2.setSampleGroupName("sample");
  meta_data2.setSequenceSegmentName("sequence_segment2");
  meta_data2.setSampleType(SampleType::Unknown);
  meta_data2.acq_method_name = "6";
  meta_data2.inj_volume = 7.0;
  meta_data2.inj_volume_units = "8";
  meta_data2.batch_name = "9";
  OpenMS::FeatureMap featuremap2;
  featuremap2.setMetaValue("foo2", "bar2");

  MetaDataHandler meta_data3;
  meta_data3.setFilename("file3");
  meta_data3.setSampleName("sample3");
  meta_data3.setSampleGroupName("sample");
  meta_data3.setSequenceSegmentName("sequence_segment2");
  meta_data3.setSampleType(SampleType::Unknown);
  meta_data3.acq_method_name = "6";
  meta_data3.inj_volume = 7.0;
  meta_data3.inj_volume_units = "8";
  meta_data3.batch_name = "9";
  OpenMS::FeatureMap featuremap3;
  featuremap3.setMetaValue("foo3", "bar3");

  SequenceHandler sequenceHandler;
  sequenceHandler.addSampleToSequence(meta_data1, featuremap1);
  sequenceHandler.addSampleToSequence(meta_data2, featuremap2);
  sequenceHandler.addSampleToSequence(meta_data3, featuremap3);

  BOOST_CHECK_EQUAL(sequenceHandler.getSequence().size(), 3);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getMetaData().getSequenceSegmentName(), "sequence_segment1");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getMetaData().getSampleName(), "sample1");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureMap().metaValueExists("foo1"), true);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureMap().getMetaValue("foo1"), "bar1");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureMapHistory().metaValueExists("foo1"), true);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureMapHistory().getMetaValue("foo1"), "bar1");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getParameters().size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getTargetedExperiment().getTransitions().size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureRSDFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureRSDQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureBackgroundFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureBackgroundQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureRSDEstimations().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureBackgroundEstimations().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getQuantitationMethods().size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getMetaData().getSequenceSegmentName(), "sequence_segment2");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getMetaData().getSampleGroupName(), "sample");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureMap().metaValueExists("foo2"), true);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureMap().getMetaValue("foo2"), "bar2");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureMapHistory().metaValueExists("foo2"), true);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureMapHistory().getMetaValue("foo2"), "bar2");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getParameters().size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getTargetedExperiment().getTransitions().size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureRSDFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureRSDQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureBackgroundFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureBackgroundQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureRSDEstimations().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureBackgroundEstimations().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getQuantitationMethods().size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getMetaData().getSampleType() == SampleType::Unknown, true);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getMetaData().getSequenceSegmentName(), "sequence_segment2");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getMetaData().getSampleGroupName(), "sample");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureMap().metaValueExists("foo3"), true);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureMap().getMetaValue("foo3"), "bar3");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureMapHistory().metaValueExists("foo3"), true);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureMapHistory().getMetaValue("foo3"), "bar3");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getParameters().size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getTargetedExperiment().getTransitions().size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureRSDFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureRSDQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureBackgroundFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureBackgroundQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureRSDEstimations().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureBackgroundEstimations().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getQuantitationMethods().size(), 0);

  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getSequenceSegmentName(), "sequence_segment1");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getQuantitationMethods().size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getFeatureFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getFeatureQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getFeatureRSDFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getFeatureRSDQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getFeatureBackgroundFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getFeatureBackgroundQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getFeatureRSDEstimations().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getFeatureBackgroundEstimations().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getSampleIndices().size(), 1);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getSampleIndices()[0], 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getSequenceSegmentName(), "sequence_segment2");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getQuantitationMethods().size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getFeatureFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getFeatureQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getFeatureRSDFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getFeatureRSDQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getFeatureBackgroundFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getFeatureBackgroundQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getFeatureRSDEstimations().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getFeatureBackgroundEstimations().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getSampleIndices().size(), 2);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getSampleIndices()[0], 1);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getSampleIndices()[1], 2);

  BOOST_CHECK_EQUAL(sequenceHandler.getSampleGroups()[0].getSampleGroupName(), "sample");
  BOOST_CHECK_EQUAL(sequenceHandler.getSampleGroups()[0].getSampleIndices().size(), 3);
  BOOST_CHECK_EQUAL(sequenceHandler.getSampleGroups()[0].getSampleIndices()[0], 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSampleGroups()[0].getSampleIndices()[1], 1);
  BOOST_CHECK_EQUAL(sequenceHandler.getSampleGroups()[0].getSampleIndices()[2], 2);

  // Test non-shared resources
  InjectionHandler& injection0 = sequenceHandler.getSequence()[0];
  injection0.getMetaData().setSampleName("samp1");
  BOOST_CHECK_EQUAL(injection0.getRawData().getMetaData().getSampleName(), "samp1");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getMetaData().getSampleName(), "samp1");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getMetaData().getSampleName(), "sample2");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getMetaData().getSampleName(), "sample3");
  // TODO: What happens if the user modifies the sequence segment name?
  //       Need to implement a method that re-organizes the sequence segments if the sequence segment name attribute is modified!

  // Test shared resources across all raw data handlers
  auto param1 = Parameter("param1", 0);
  param1.setName("param1");
  FunctionParameters params("MRMFeatureFinderScoring");
  params.addParameter(param1);
  ParameterSet parameters;
  parameters.addFunctionParameters(params);
  injection0.getRawData().getParameters() = parameters;
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getParameters().at("MRMFeatureFinderScoring")[0].getName(), "param1");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getParameters().at("MRMFeatureFinderScoring")[0].getName(), "param1");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getParameters().at("MRMFeatureFinderScoring")[0].getName(), "param1");
  OpenMS::ReactionMonitoringTransition srm;
  srm.setPeptideRef("arg-L");
  injection0.getRawData().getTargetedExperiment().setTransitions({srm});
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getTargetedExperiment().getTransitions()[0].getPeptideRef(), "arg-L");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getTargetedExperiment().getTransitions()[0].getPeptideRef(), "arg-L");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getTargetedExperiment().getTransitions()[0].getPeptideRef(), "arg-L");

  // Test shared resources across sequence segment handlers
  sequenceHandler.getSequenceSegments()[0].getQuantitationMethods().resize(1);
  sequenceHandler.getSequenceSegments()[0].getQuantitationMethods()[0].setComponentName("23dpg.23dpg_1.Light");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getQuantitationMethods()[0].getComponentName(), "23dpg.23dpg_1.Light");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getQuantitationMethods().size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getQuantitationMethods().size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getQuantitationMethods()[0].getComponentName(), "23dpg.23dpg_1.Light");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getQuantitationMethods().size(), 0);
  sequenceHandler.getSequenceSegments()[0].getFeatureFilter().component_qcs.resize(1);
  sequenceHandler.getSequenceSegments()[0].getFeatureFilter().component_qcs[0].component_name = "arg-L.arg-L_1.Heavy";
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureFilter().component_qcs[0].component_name, "arg-L.arg-L_1.Heavy");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getFeatureFilter().component_qcs[0].component_name, "arg-L.arg-L_1.Heavy");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getFeatureFilter().component_qcs.size(), 0);
  sequenceHandler.getSequenceSegments()[0].getFeatureQC().component_qcs.resize(1);
  sequenceHandler.getSequenceSegments()[0].getFeatureQC().component_qcs[0].component_name = "arg-L.arg-L_1.Light";
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureQC().component_qcs[0].component_name, "arg-L.arg-L_1.Light");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getFeatureQC().component_qcs[0].component_name, "arg-L.arg-L_1.Light");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getFeatureQC().component_qcs.size(), 0);
  sequenceHandler.getSequenceSegments()[0].getFeatureRSDFilter().component_qcs.resize(1);
  sequenceHandler.getSequenceSegments()[0].getFeatureRSDFilter().component_qcs[0].component_name = "trp-L.trp-L_1.Heavy";
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureRSDFilter().component_qcs[0].component_name, "trp-L.trp-L_1.Heavy");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureRSDFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureRSDFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getFeatureRSDFilter().component_qcs[0].component_name, "trp-L.trp-L_1.Heavy");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getFeatureRSDFilter().component_qcs.size(), 0);
  sequenceHandler.getSequenceSegments()[0].getFeatureRSDQC().component_qcs.resize(1);
  sequenceHandler.getSequenceSegments()[0].getFeatureRSDQC().component_qcs[0].component_name = "trp-L.trp-L_1.Light";
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureRSDQC().component_qcs[0].component_name, "trp-L.trp-L_1.Light");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureRSDQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureRSDQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getFeatureRSDQC().component_qcs[0].component_name, "trp-L.trp-L_1.Light");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getFeatureRSDQC().component_qcs.size(), 0);
  sequenceHandler.getSequenceSegments()[0].getFeatureBackgroundFilter().component_qcs.resize(1);
  sequenceHandler.getSequenceSegments()[0].getFeatureBackgroundFilter().component_qcs[0].component_name = "ala-L.ala-L_1.Heavy";
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureBackgroundFilter().component_qcs[0].component_name, "ala-L.ala-L_1.Heavy");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureBackgroundFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureBackgroundFilter().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getFeatureBackgroundFilter().component_qcs[0].component_name, "ala-L.ala-L_1.Heavy");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getFeatureBackgroundFilter().component_qcs.size(), 0);
  sequenceHandler.getSequenceSegments()[0].getFeatureBackgroundQC().component_qcs.resize(1);
  sequenceHandler.getSequenceSegments()[0].getFeatureBackgroundQC().component_qcs[0].component_name = "ala-L.ala-L_1.Light";
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureBackgroundQC().component_qcs[0].component_name, "ala-L.ala-L_1.Light");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureBackgroundQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureBackgroundQC().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getFeatureBackgroundQC().component_qcs[0].component_name, "ala-L.ala-L_1.Light");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getFeatureBackgroundQC().component_qcs.size(), 0);
  sequenceHandler.getSequenceSegments()[0].getFeatureRSDEstimations().component_qcs.resize(1);
  sequenceHandler.getSequenceSegments()[0].getFeatureRSDEstimations().component_qcs[0].component_name = "glu-L.glu-L_1.Heavy";
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureRSDEstimations().component_qcs[0].component_name, "glu-L.glu-L_1.Heavy");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureRSDEstimations().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureRSDEstimations().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getFeatureRSDEstimations().component_qcs[0].component_name, "glu-L.glu-L_1.Heavy");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getFeatureRSDEstimations().component_qcs.size(), 0);
  sequenceHandler.getSequenceSegments()[0].getFeatureBackgroundEstimations().component_qcs.resize(1);
  sequenceHandler.getSequenceSegments()[0].getFeatureBackgroundEstimations().component_qcs[0].component_name = "glu-L.glu-L_1.Light";
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[0].getRawData().getFeatureBackgroundEstimations().component_qcs[0].component_name, "glu-L.glu-L_1.Light");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[1].getRawData().getFeatureBackgroundEstimations().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequence()[2].getRawData().getFeatureBackgroundEstimations().component_qcs.size(), 0);
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[0].getFeatureBackgroundEstimations().component_qcs[0].component_name, "glu-L.glu-L_1.Light");
  BOOST_CHECK_EQUAL(sequenceHandler.getSequenceSegments()[1].getFeatureBackgroundEstimations().component_qcs.size(), 0);
}

BOOST_AUTO_TEST_CASE(getMetaValue)
{
  SequenceHandler sequenceHandler;
  OpenMS::Feature feature;
  feature.setRT(16.0);
  feature.setIntensity(1.0e4);
  OpenMS::Feature subordinate;
  subordinate.setIntensity(1.0e2);
  subordinate.setMetaValue("calculated_concentration", 10.0);
  subordinate.setMetaValue("validation", "FP");

  CastValue result;

  result = SequenceHandler::getMetaValue(feature, subordinate, "RT");
  BOOST_CHECK_EQUAL(result.getTag() == CastValue::Type::FLOAT, true);
  BOOST_CHECK_CLOSE(result.f_, 16.0, 1e-6);

  result = SequenceHandler::getMetaValue(feature, subordinate, "intensity");
  BOOST_CHECK_EQUAL(result.getTag() == CastValue::Type::FLOAT, true);
  BOOST_CHECK_CLOSE(result.f_, 1.0e4, 1e-6);

  result = SequenceHandler::getMetaValue(feature, subordinate, "peak_area");
  BOOST_CHECK_EQUAL(result.getTag() == CastValue::Type::FLOAT, true);
  BOOST_CHECK_CLOSE(result.f_, 1.0e2, 1e-6);

  result = SequenceHandler::getMetaValue(feature, subordinate, "calculated_concentration");
  BOOST_CHECK_EQUAL(result.getTag() == CastValue::Type::FLOAT, true);
  BOOST_CHECK_CLOSE(result.f_, 10.0, 1e-6);

  result = SequenceHandler::getMetaValue(feature, subordinate, "absent_meta_value");
  BOOST_CHECK_EQUAL(result.getTag() == CastValue::Type::STRING, true);
  BOOST_CHECK_EQUAL(result.s_, "");

  result = SequenceHandler::getMetaValue(feature, subordinate, "validation");
  BOOST_CHECK_EQUAL(result.getTag() == CastValue::Type::STRING, true);
  BOOST_CHECK_EQUAL(result.s_, "FP");
}

BOOST_AUTO_TEST_CASE(getSamplesInSequence)
{
  MetaDataHandler meta_data1;
  meta_data1.setFilename("file1");
  meta_data1.setSampleName("sample1");
  meta_data1.setSampleGroupName("sample");
  meta_data1.setSequenceSegmentName("sequence_segment");
  meta_data1.setSampleType(SampleType::Unknown);
  meta_data1.acq_method_name = "6";
  meta_data1.inj_volume = 7.0;
  meta_data1.inj_volume_units = "8";
  meta_data1.batch_name = "9";

  MetaDataHandler meta_data2;
  meta_data2.setFilename("file2");
  meta_data2.setSampleName("sample2");
  meta_data2.setSampleGroupName("sample");
  meta_data2.setSequenceSegmentName("sequence_segment");
  meta_data2.setSampleType(SampleType::Unknown);
  meta_data2.acq_method_name = "6";
  meta_data2.inj_volume = 7.0;
  meta_data2.inj_volume_units = "8";
  meta_data2.batch_name = "9";

  MetaDataHandler meta_data3;
  meta_data3.setFilename("file3");
  meta_data3.setSampleName("sample3");
  meta_data3.setSampleGroupName("sample");
  meta_data3.setSequenceSegmentName("sequence_segment");
  meta_data3.setSampleType(SampleType::Unknown);
  meta_data3.acq_method_name = "6";
  meta_data3.inj_volume = 7.0;
  meta_data3.inj_volume_units = "8";
  meta_data3.batch_name = "9";

  OpenMS::FeatureMap featuremap;

  SequenceHandler sequenceHandler;
  sequenceHandler.addSampleToSequence(meta_data1, featuremap);
  sequenceHandler.addSampleToSequence(meta_data2, featuremap);
  sequenceHandler.addSampleToSequence(meta_data3, featuremap);

  const set<string> injection_names = {
    "sample1_-1_9_1900-01-01_000000",
    "foo",
    "sample3_-1_9_1900-01-01_000000"
  };

  const std::vector<InjectionHandler> samples = sequenceHandler.getSamplesInSequence(injection_names);

  BOOST_CHECK_EQUAL(samples.size(), 2);
  BOOST_CHECK_EQUAL(samples[0].getMetaData().getSampleName(), "sample1");
  BOOST_CHECK_EQUAL(samples[1].getMetaData().getSampleName(), "sample3");
}

BOOST_AUTO_TEST_SUITE_END()
