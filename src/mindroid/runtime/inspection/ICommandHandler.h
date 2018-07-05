/*
 * Copyright (C) 2018 E.S.R.Labs
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

#ifndef MINDROID_RUNTIME_INSPECTION_ICOMMANDHANDLER_H_
#define MINDROID_RUNTIME_INSPECTION_ICOMMANDHANDLER_H_

#include <mindroid/os/Binder.h>
#include <mindroid/lang/StringArray.h>

namespace mindroid {

class Intent;

class ICommandHandler :
        public IInterface {
public:
    virtual sp<Promise<sp<String>>> execute(const sp<StringArray>& arguments) = 0;
};

namespace binder {

class CommandHandler {
public:
    class Proxy;

    class Stub : public Binder, public ICommandHandler {
    public:
        Stub() {
            attachInterface(this, String::valueOf(DESCRIPTOR));
        }

        static sp<ICommandHandler> asInterface(const sp<IBinder>& binder) {
            if (binder == nullptr) {
                return nullptr;
            }
            return new CommandHandler::Proxy(binder);
        }

        sp<IBinder> asBinder() override {
            return this;
        }

        void onTransact(int32_t what, int32_t num, const sp<Object>& obj, const sp<Bundle>& data, const sp<Promise<sp<Object>>>& result) override;

        class Proxy : public ICommandHandler {
        public:
            Proxy(const sp<IBinder>& remote) {
                mRemote = remote;
            }

            sp<IBinder> asBinder() override {
                return mRemote;
            }

            bool equals(const sp<Object>& obj) const override {
                if (obj == nullptr) return false;
                if (obj == this) return true;
                if (Class<Stub::Proxy>::isInstance(obj)) {
                    sp<Stub::Proxy> other = Class<Stub::Proxy>::cast(obj);
                    return mRemote->equals(other->mRemote);
                } else {
                    return false;
                }
            }

            size_t hashCode() const override {
                return mRemote->hashCode();
            }

            sp<Promise<sp<String>>> execute(const sp<StringArray>& arguments) override;

        private:
            sp<IBinder> mRemote;
        };

    private:
        static const char* const DESCRIPTOR;
        static const int32_t MSG_EXECUTE = 1;

        friend class CommandHandler::Proxy;
    };

    class Proxy : public ICommandHandler {
    public:
        Proxy(const sp<IBinder>& binder);

        sp<IBinder> asBinder() override {
            return mBinder;
        }

        bool equals(const sp<Object>& obj) const override {
            if (obj == nullptr) return false;
            if (obj == this) return true;
            if (Class<Proxy>::isInstance(obj)) {
                sp<Proxy> other = Class<Proxy>::cast(obj);
                return mBinder->equals(other->mBinder);
            } else {
                return false;
            }
        }

        size_t hashCode() const override {
            return mBinder->hashCode();
        }

        sp<Promise<sp<String>>> execute(const sp<StringArray>& arguments) override;

    private:
        sp<IBinder> mBinder;
        sp<CommandHandler::Stub> mStub;
        sp<ICommandHandler> mProxy;
    };
};

} /* namespace binder */
} /* namespace mindroid */

#endif /* MINDROID_RUNTIME_INSPECTION_ICOMMANDHANDLER_H_ */