/*
 *  Copyright (c) 2012 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "modules/audio_coding/neteq/include/neteq.h"

#include <memory>
#include <sstream>

#include "modules/audio_coding/neteq/neteq_impl.h"

namespace webrtc {

NetEq::Config::Config() = default;
NetEq::Config::Config(const Config&) = default;
NetEq::Config::Config(Config&&) = default;
NetEq::Config::~Config() = default;
NetEq::Config& NetEq::Config::operator=(const Config&) = default;
NetEq::Config& NetEq::Config::operator=(Config&&) = default;

std::string NetEq::Config::ToString() const {
  std::stringstream ss;
  ss << "sample_rate_hz=" << sample_rate_hz
     << ", enable_post_decode_vad="
     << (enable_post_decode_vad ? "true" : "false")
     << ", max_packets_in_buffer=" << max_packets_in_buffer
     << ", playout_mode=" << playout_mode
     << ", enable_fast_accelerate="
     << (enable_fast_accelerate ? " true": "false")
     << ", enable_muted_state=" << (enable_muted_state ? " true": "false");
  return ss.str();
}

// Creates all classes needed and inject them into a new NetEqImpl object.
// Return the new object.
NetEq* NetEq::Create(
    const NetEq::Config& config,
    const rtc::scoped_refptr<AudioDecoderFactory>& decoder_factory) {
  return new NetEqImpl(config,
                       NetEqImpl::Dependencies(config, decoder_factory));
}

}  // namespace webrtc
