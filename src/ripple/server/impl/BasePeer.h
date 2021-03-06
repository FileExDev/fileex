

#ifndef RIPPLE_SERVER_BASEPEER_H_INCLUDED
#define RIPPLE_SERVER_BASEPEER_H_INCLUDED

#include <ripple/server/Port.h>
#include <ripple/server/impl/io_list.h>
#include <ripple/server/impl/LowestLayer.h>
#include <ripple/beast/utility/WrappedSink.h>
#include <boost/asio.hpp>
#include <atomic>
#include <cassert>
#include <functional>
#include <string>

namespace ripple {

template<class Handler, class Impl>
class BasePeer
    : public io_list::work
{
protected:
    using clock_type = std::chrono::system_clock;
    using error_code = boost::system::error_code;
    using endpoint_type = boost::asio::ip::tcp::endpoint;
    using waitable_timer = boost::asio::basic_waitable_timer <clock_type>;

    Port const& port_;
    Handler& handler_;
    endpoint_type remote_address_;
    beast::WrappedSink sink_;
    beast::Journal j_;

    boost::asio::executor_work_guard<boost::asio::executor> work_;
    boost::asio::strand<boost::asio::executor> strand_;
public:
    BasePeer(
        Port const& port,
        Handler& handler,
        boost::asio::executor const& executor,
        endpoint_type remote_address,
        beast::Journal journal);

    void
    close() override;

private:
    Impl&
    impl()
    {
        return *static_cast<Impl*>(this);
    }
};


template <class Handler, class Impl>
BasePeer<Handler, Impl>::BasePeer(
    Port const& port,
    Handler& handler,
    boost::asio::executor const& executor,
    endpoint_type remote_address,
    beast::Journal journal)
    : port_(port)
    , handler_(handler)
    , remote_address_(remote_address)
    , sink_(
          journal.sink(),
          [] {
              static std::atomic<unsigned> id{0};
              return "##" + std::to_string(++id) + " ";
          }())
    , j_(sink_)
    , work_(executor)
    , strand_(executor)
{
}

template<class Handler, class Impl>
void
BasePeer<Handler, Impl>::
close()
{
    if (! strand_.running_in_this_thread())
        return post(
            strand_, std::bind(&BasePeer::close, impl().shared_from_this()));
    error_code ec;
    ripple::get_lowest_layer(impl().ws_).close(ec);
}

} 

#endif








