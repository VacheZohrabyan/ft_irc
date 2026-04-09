#pragma once

#include "../include.hpp"
#include "../utils.hpp"

class Client;

class Chanel
{
public:
    Chanel();
    Chanel& operator=(const Chanel& other);
    Chanel(const std::string& name, int fd, const std::string& chanelKey);
    ~Chanel();

private:
    std::string _chanelName;
    std::string _chanelkey;
    std::string _chanelTopic;
    int _chanelRootFd;
    std::size_t _maxCountUser;
    std::map<int, std::string> _clients;
    std::time_t _createTime;
    
public:
    void addClient(int fd, const std::string& name);
    void removeChanel(int fd);
    bool hasClient(int fd);
    void showAll(int fd, const Client& client);
    void broadCast(const std::string& message, int all);
    
public:
    // const std::map<int, std::string>& getUserNick() const;
    std::string getTopic() const;
    void setTopic(const std::string& topic);
    std::size_t getCountClient() const;
    std::size_t getMaxCount() const;
    void setMaxCount(std::size_t count);
    int getRootFd() const;
    const std::time_t& getTime() const;

private:
    bool _inviteOnly;
    bool _topicProtection;
    bool _chanelPasswd;
    bool _operatorPrivilege;
    bool _limit;

public:
    bool getLimit() const;
    void setLimit(bool limit);
    bool getInviteOnly() const;
    void setInviteOnly(bool inviteOnly);
    bool getTopicProtection() const;
    void setTopicProtection(bool topicprotection);
    bool getChanelPasswd() const;
    void setChanelPasswd(bool chanelPasswd);
    bool getOperatorPrivilege() const;
    void setOperatorPrivilege(bool operatorPrivilege);
};