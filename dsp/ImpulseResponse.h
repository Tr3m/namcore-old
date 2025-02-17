//
//  ImpulseResponse.h
//  NeuralAmpModeler-macOS
//
//  Created by Steven Atkinson on 12/30/22.
//
// Impulse response processing

#pragma once

#include <filesystem>

#include <Eigen/Dense>

#include "coredsp.h"
#include "wav.h"

namespace dsp
{
template <typename SampleType>
class ImpulseResponse : public History<SampleType>
{
public:
  ImpulseResponse(const char* fileName, const SampleType sampleRate);
  SampleType** Process(SampleType** inputs, const size_t numChannels, const size_t numFrames) override;
  // TODO states for the IR class
  dsp::wav::LoadReturnCode GetWavState() const { return this->mWavState; };

private:
  // Set the weights, given that the plugin is running at the provided sample
  // rate.
  void _SetWeights(const SampleType sampleRate);

  // State of audio
  dsp::wav::LoadReturnCode mWavState;
  // Keep a copy of the raw audio that was loaded so that it can be resampled
  std::vector<float> mRawAudio;
  SampleType mRawAudioSampleRate;
  // Resampled to the required sample rate.
  std::vector<float> mResampled;

  const size_t mMaxLength = 8192;
  // The weights
  Eigen::VectorXf mWeight;
};
}; // namespace dsp
