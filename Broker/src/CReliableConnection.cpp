
////////////////////////////////////////////////////////////////////
/// @file      CConnection.cpp
///
/// @author    Derek Ditch <derek.ditch@mst.edu>
///            Christopher M. Kohlhoff <chris@kohlhoff.com> (Boost Example)
///            Stephen Jackson <scj7t4@mst.edu>
///
/// @compiler  C++
///
/// @project   FREEDM DGI
///
/// @description 
///
/// @license
/// These source code files were created at as part of the
/// FREEDM DGI Subthrust, and are
/// intended for use in teaching or research.  They may be 
/// freely copied, modified and redistributed as long
/// as modified versions are clearly marked as such and
/// this notice is not removed.
/// 
/// Neither the authors nor the FREEDM Project nor the
/// National Science Foundation
/// make any warranty, express or implied, nor assumes
/// any legal responsibility for the accuracy,
/// completeness or usefulness of these codes or any
/// information distributed with these codes.
///
/// Suggested modifications or questions about these codes 
/// can be directed to Dr. Bruce McMillin, Department of 
/// Computer Science, Missouri University of Science and
/// Technology, Rolla, MO  65409 (ff@mst.edu).
////////////////////////////////////////////////////////////////////

#include "CDispatcher.hpp"
#include "CReliableConnection.hpp"
#include "CConnectionManager.hpp"
#include "CMessage.hpp"
#include "RequestParser.hpp"
#include "CLogger.hpp"

#include <vector>

#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;

namespace freedm {
    namespace broker {

static CLocalLogger Logger(__FILE__);
        
///////////////////////////////////////////////////////////////////////////////
/// @fn CReliableConnection::CReliableConnection
/// @description: Constructor for the CGenericConnection object.
/// @pre: An initialized socket is ready to be converted to a connection.
/// @post: A new CConnection object is initialized.
/// @param p_ioService: The socket to use for the connection.
/// @param p_manager: The related connection manager that tracks this object.
/// @param p_dispatch: The dispatcher responsible for applying read/write 
///   handlers to messages.
/// @param uuid: The uuid this node connects to, or what listener.
///////////////////////////////////////////////////////////////////////////////
CReliableConnection::CReliableConnection(boost::asio::io_service& p_ioService,
  CConnectionManager& p_manager, CBroker& p_broker, std::string uuid)
  : m_socket(p_ioService),
    m_connManager(p_manager),
    m_broker(p_broker),
    m_uuid(uuid)
{
    Logger.Debug << __PRETTY_FUNCTION__ << std::endl;
    m_reliability = 100;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn CReliableConnection::GetSocket
/// @description Returns the socket used by this node.
/// @pre None
/// @post None
/// @return A reference to the socket used by this connection.
///////////////////////////////////////////////////////////////////////////////
boost::asio::ip::udp::socket& CReliableConnection::GetSocket()
{
    Logger.Debug << __PRETTY_FUNCTION__ << std::endl;

    return m_socket;
}


/// Get associated UUID
std::string CReliableConnection::GetUUID()
{
    return m_uuid;
}

/// Get Connection Manager
CConnectionManager& CReliableConnection::GetConnectionManager() {
    return m_connManager;
}

/// Get the broker
CBroker& CReliableConnection::GetBroker() {
    return m_broker;
}

/// Get the dispatcher
CDispatcher& CReliableConnection::GetDispatcher() {
    return m_broker.GetDispatcher();
}

/// Get the ioservice
boost::asio::io_service& CReliableConnection::GetIOService()
{
    return m_socket.get_io_service();
}

/// Set the connection reliability for DCUSTOMNETWORK
void CReliableConnection::SetReliability(int r)
{
    m_reliability = r;
}

/// Get the connection reliability for DCUSTOMNETWORK
int CReliableConnection::GetReliability()
{
    return m_reliability;
}


    } // namespace broker
} // namespace freedm
