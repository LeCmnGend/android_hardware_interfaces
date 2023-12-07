/*
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <android/hardware/tv/cec/1.0/IHdmiCec.h>
#include <hardware/hdmi_cec.h>

namespace android {
namespace hardware {
namespace tv {
namespace cec {
namespace V1_0 {
namespace implementation {

struct HdmiCecDefault : public IHdmiCec, public hidl_death_recipient {
    HdmiCecDefault();
    ~HdmiCecDefault();
    // Methods from ::android::hardware::tv::cec::V1_0::IHdmiCec follow.
    Return<Result> addLogicalAddress(CecLogicalAddress addr) override;
    Return<void> clearLogicalAddress() override;
    Return<void> getPhysicalAddress(getPhysicalAddress_cb _hidl_cb) override;
    Return<SendMessageResult> sendMessage(const CecMessage& message) override;
    Return<void> setCallback(const sp<IHdmiCecCallback>& callback) override;
    Return<int32_t> getCecVersion() override;
    Return<uint32_t> getVendorId() override;
    Return<void> getPortInfo(getPortInfo_cb _hidl_cb) override;
    Return<void> setOption(OptionKey key, bool value) override;
    Return<void> setLanguage(const hidl_string& language) override;
    Return<void> enableAudioReturnChannel(int32_t portId, bool enable) override;
    Return<bool> isConnected(int32_t portId) override;

    virtual void serviceDied(uint64_t, const wp<::android::hidl::base::V1_0::IBase>&) {
        setCallback(nullptr);
    }

    Return<Result> init();
    Return<void> release();
    static void* event_thread(void*);
    static int getOpcode(struct cec_msg message);
    static bool isWakeupMessage(struct cec_msg message);
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace cec
}  // namespace tv
}  // namespace hardware
}  // namespace android
