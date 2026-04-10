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
    std::set<int> _chanelRootFd;
    std::size_t _maxCountUser;
    std::map<int, std::string> _clients;
    std::time_t _createTime;
    
public:
    void addClient(int fd, const std::string& name);
    void removeChanel(int fd);
    bool hasClient(int fd);
    bool hasClient(const std::string& nick) const;
    void showAll(int fd, const Client& client);
    void broadCast(const std::string& message, int all);
    
public:
    void setTopic(const std::string& topic);
    void setMaxCount(std::size_t count);
    void setChanelKey(const std::string& pass);

public:
    const std::string& getChanelName() const;
    const std::string& getChannelPass() const;
    const std::time_t& getTime() const;
    std::string getTopic() const;
    const std::set<int>& getRootFd() const;
    void removeRootFd(int fd);
    std::size_t getCountClient() const;
    std::size_t getMaxCount() const;

private:
    bool _inviteOnly;
    bool _topicProtection;
    bool _chanelPasswd;
    bool _operatorPrivilege;
    bool _limit;

public:
    bool getLimit() const;
    bool getInviteOnly() const;
    bool getTopicProtection() const;
    bool getChanelPasswd() const;
    bool getOperatorPrivilege(int fd) const;

public:
    void setLimit(bool limit);
    void setInviteOnly(bool inviteOnly);
    void setTopicProtection(bool topicprotection);
    void setChanelPasswd(bool chanelPasswd);
    void setOperatorPrivilege(int fd);
};