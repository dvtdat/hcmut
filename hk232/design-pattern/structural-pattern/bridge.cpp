#include <bits/stdc++.h>

using namespace std;

// Interface for all implementation classes
class Device {
public:
    virtual ~Device() = default;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual int getVolume() = 0;
    virtual void setVolume(int volume) = 0;
    virtual int getChannel() = 0;
    virtual void setChannel(int channel) = 0;
    virtual bool isEnable() = 0;
};

class TV : public Device {
private:
    int volume;
    int channel;
    bool enable;

public:
    TV() : volume(0), channel(0), enable(false) {}
    void turnOn() override {
        cout << "TV is on" << endl;
    }

    void turnOff() override {
        cout << "TV is off" << endl;
    }

    int getVolume() override {
        return volume;
    }

    void setVolume(int volume) override {
        this->volume = volume;
    }

    int getChannel() override {
        return channel;
    }

    void setChannel(int channel) override {
        this->channel = channel;
    }

    bool isEnable() {
        return enable;
    }
};

class Radio : public Device {
private:
    int volume;
    int channel;
    bool enable;

public:
    Radio() : volume(0), channel(0), enable(false) {}
    void turnOn() override {
        cout << "Radio is on" << endl;
    }

    void turnOff() override {
        cout << "Radio is off" << endl;
    }

    int getVolume() override {
        return volume;
    }

    void setVolume(int volume) override {
        this->volume = volume;
    }

    int getChannel() override {
        return channel;
    }

    void setChannel(int channel) override {
        this->channel = channel;
    }

    bool isEnable() {
        return enable;
    }
};

class RemoteControl {
protected:
    Device *device;

public:
    RemoteControl() : device(nullptr) {}
    RemoteControl(Device *device) : device(device) {}
    virtual ~RemoteControl() = default;
    virtual void togglePower() = 0;
    virtual void volumeUp() = 0;
    virtual void volumeDown() = 0;
    virtual void channelUp() = 0;
    virtual void channelDown() = 0;
};

class MinimalisticRemoteControl : public RemoteControl {
public:
    MinimalisticRemoteControl() : RemoteControl() {}
    MinimalisticRemoteControl(Device *device) : RemoteControl(device) {}
    
    void togglePower() override {
        if (device == nullptr) {
            cout << "No device is connected" << endl;
            return;
        }
        if (device->isEnable()) {
            device->turnOff();
        } else {
            device->turnOn();
        }
    }

    void volumeUp() override {
        if (device == nullptr) {
            cout << "No device is connected" << endl;
            return;
        }
        device->setVolume(device->getVolume() + 10);
    }

    void volumeDown() override {
        if (device == nullptr) {
            cout << "No device is connected" << endl;
            return;
        }
        device->setVolume(device->getVolume() - 10);
    }

    void channelUp() override {
        if (device == nullptr) {
            cout << "No device is connected" << endl;
            return;
        }
        device->setChannel(device->getChannel() + 10);
    }
    
    void channelDown() override {
        if (device == nullptr) {
            cout << "No device is connected" << endl;
            return;
        }
        device->setChannel(device->getChannel() - 10);
    }
};

class SofisticatedRemoteControl : public RemoteControl {
public:
    SofisticatedRemoteControl() : RemoteControl() {}
    SofisticatedRemoteControl(Device *device) : RemoteControl(device) {}
    
    void togglePower() override {
        if (device == nullptr) {
            cout << "No device is connected" << endl;
            return;
        }
        if (device->isEnable()) {
            device->turnOff();
        } else {
            device->turnOn();
        }
    }

    void volumeUp() override {
        if (device == nullptr) {
            cout << "No device is connected" << endl;
            return;
        }
        device->setVolume(device->getVolume() + 1);
    }

    void volumeDown() override {
        if (device == nullptr) {
            cout << "No device is connected" << endl;
            return;
        }
        device->setVolume(device->getVolume() - 1);
    }

    void channelUp() override {
        if (device == nullptr) {
            cout << "No device is connected" << endl;
            return;
        }
        device->setChannel(device->getChannel() + 1);
    }
    
    void channelDown() override {
        if (device == nullptr) {
            cout << "No device is connected" << endl;
            return;
        }
        device->setChannel(device->getChannel() - 1);
    }

    // Additional method: setChannel
    void setChannel(int channel) {
        if (device == nullptr) {
            cout << "No device is connected" << endl;
            return;
        }
        device->setChannel(channel);
    }

    // Additional method: mute
    void mute() {
        if (device == nullptr) {
            cout << "No device is connected" << endl;
            return;
        }
        device->setVolume(0);
    }
};

class Client {
public:
    static void turnOnDevice(RemoteControl *remoteControl) {
        remoteControl->togglePower();
    }

    static void turnOffDevice(RemoteControl *remoteControl) {
        remoteControl->togglePower();
    }

    static void volumeUp(RemoteControl *remoteControl) {
        remoteControl->volumeUp();
    }

    static void volumeDown(RemoteControl *remoteControl) {
        remoteControl->volumeDown();
    }

    static void mute(RemoteControl *remoteControl) {
        if (dynamic_cast<SofisticatedRemoteControl*>(remoteControl) == nullptr) {
            cout << "This remote control does not support mute" << endl;
            return;
        }
        dynamic_cast<SofisticatedRemoteControl*>(remoteControl)->mute();
    }
};


int main() {
    MinimalisticRemoteControl* remoteControlRadio = new MinimalisticRemoteControl(new Radio()); // using minimalistic remote control to control radio
    SofisticatedRemoteControl* remoteControlTV = new SofisticatedRemoteControl(new TV()); // using sofisticated remote control to control TV

    Client::turnOnDevice(remoteControlRadio);
    Client::mute(remoteControlRadio);
}