//
// Copyright (c) 2019-2024 Ruben Perez Hidalgo (rubenperez038 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

//[example_tutorial_sync

/**
 * Creates a connection, establishes a session and
 * runs a simple "Hello world!" query.
 *
 * This example uses synchronous functions and handles errors using exceptions.
 */

#include <boost/mysql/any_connection.hpp>
#include <boost/mysql/connect_params.hpp>
#include <boost/mysql/error_with_diagnostics.hpp>
#include <boost/mysql/results.hpp>

#include <boost/asio/io_context.hpp>

#include <iostream>

//[tutorial_sync_namespaces
namespace mysql = boost::mysql;
namespace asio = boost::asio;
//]

static void main_impl()
{
    const char* hostname = "localhost";
    const char* username = "root";
    const char* password = "123456";
    asio::io_context ctx;
    mysql::any_connection conn(ctx);
    mysql::connect_params params;
    params.server_address.emplace_host_and_port(hostname);
    params.username = username;
    params.password = password;
    conn.connect(params);
    const char* sql = "show databases";
    mysql::results result;
    conn.execute(sql, result);
    std::cout << result.rows().at(0).at(0) << std::endl;
    conn.close();
}

void test_mysql()
{
    try{
      main_impl();
    }catch (const mysql::error_with_diagnostics& err){
        std::cerr << "Error: " << err.what() << '\n'
                  << "Server diagnostics: " << err.get_diagnostics().server_message() << std::endl;
    }catch (const std::exception& err){
        std::cerr << "Error: " << err.what() << std::endl;
    }catch (...){
        std::cerr << "Unkonwn error..." << std::endl;
    }
}

//]
