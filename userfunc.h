#pragma once

//    Grotopia Bot
//    Copyright (C) 2018  Growtopia Noobs
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License as published
//    by the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include "json.hpp"
#include <sstream>
#include <vector>
#include <limits>
#include <math.h>
#include <string>
#include <iostream>
#include <regex>
#include <iterator>
#include <algorithm>

#include "utilsfunc.h"
#include "corefunc.h"
#include "userfunc.h"
#include "enet/include/enet.h"

//#define WORLD_GO

using namespace std;



char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7',
'8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

std::string hexStr(unsigned char data)
{
	std::string s(2, ' ');
	s[0] = hexmap[(data & 0xF0) >> 4];
	s[1] = hexmap[data & 0x0F];
	return s;
}

string generateMeta()
{
	string x;
	for (int i = 0; i < 9; i++)
	{
		x += hexStr(rand());
	}
	x += ".com";
	return x;
}

string generateMac()
{
	string x;
	for (int i = 0; i < 6; i++)
	{
		x += hexStr(rand());
		if (i != 5)
			x += ":";
	}
	return x;
}

string generateRid()
{
	string x;
	for (int i = 0; i < 16; i++)
	{
		x += hexStr(rand());
	}
	for (auto & c : x) c = toupper(c);
	return x;
}

string stripMessage(string msg) {
	regex e("\\x60[a-zA-Z0-9!@#$%^&*()_+\\-=\\[\\]\\{};':\"\\\\|,.<>\\/?]");
	string result = regex_replace(msg, e, "");
	result.erase(std::remove(result.begin(), result.end(), '`'), result.end());
	return result;
}

void GrowtopiaBot::onLoginRequested()
{
    cout << "Logging on..." << endl;

    // Data login bot
    string ver = gameVersion;
    string hash = std::to_string((unsigned int)rand());
    string hash2 = std::to_string((unsigned int)rand());
    
    // Format paket login sesuai permintaan
string packet = 
"tankIDName|BOBSQUISH\n"
"tankIDPass|12345678\n"
"requestedName|\n"
"f|1\n"
"protocol|212\n"
"game_version|5.02\n"
"cbits|0\n"
"player_age|5\n"
"GDPR|2\n"
"category|GROWMINES_3586\n"
"totalPlaytime|0\n"
"klv|90EE392D2F9D8BC997EEA41175FCD9DA\n"
"gid|a3ce687c-a505-41f8-b3d8-a9463f33f390\n"
"tr|4322\n"
"meta|InfinityPS_tXaWXoSUrGdcuETl\n"
"fhash|-716928004\n"
"rid|0215550A8186857D087474187ADCDDAF\n"
"platformID|4\n"
"deviceVersion|0\n"
"country|id\n"
"hash|1275125224\n"
"mac|02:00:00:00:00:00\n"
"wk|NONE0\n"
"lmode|1\n"
"user|516902427\n"
"UUIDToken|-1\n"
"doorID|0\n"
"aat|2\n";
	
    // Cetak isi paket untuk debugging
    cout << packet;

    // Kirim paket login
// SendPacket(2, "protocol|212\nltoken|X3Rva2VuPWRHRnVhMGxFVG1GdFpYeENUMEpUVVZWSlUwZ0tkR0Z1YTBsRVVHRnpjM3d4TWpNME5UWTNPQXB5WlhGMVpYTjBaV1JPWVcxbGZBcG1mREVLY0hKdmRHOWpiMng4TWpFeUNtZGhiV1ZmZG1WeWMybHZibncxTGpBeUNtTmlhWFJ6ZkRFd01qUUtjR3hoZVdWeVgyRm5aWHcyQ2tkRVVGSjhNZ3BqWVhSbFoyOXllWHhIVWs5WFRVbE9SVk5mTXpVNE5ncDBiM1JoYkZCc1lYbDBhVzFsZkRBS2EyeDJmRGt3UlVVek9USkVNa1k1UkRoQ1F6azVOMFZGUVRReE1UYzFSa05FT1VSQkNtZHBaSHhoTTJObE5qZzNZeTFoTlRBMUxUUXhaamd0WWpOa09DMWhPVFEyTTJZek0yWXpPVEFLZEhKOE5ETXlNZ3B0WlhSaGZFbHVabWx1YVhSNVVGTmZTSHBwWm10NlJuVnJSbGx1ZG01YVNncG1hR0Z6YUh3dE56RTJPVEk0TURBMENuSnBaSHd3TWpFMU5UVXdRVGd4T0RZNE5UZEVNRGczTkRjME1UZzNRVVJEUkVSQlJncHdiR0YwWm05eWJVbEVmRFFLWkdWMmFXTmxWbVZ5YzJsdmJud3dDbU52ZFc1MGNubDhhV1FLYUdGemFId3hNamMxTVRJMU1qSTBDbTFoWTN3d01qb3dNRG93TURvd01Eb3dNRG93TUFwM2EzeE9UMDVGTUFvPSZncm93SWQ9Qk9CU1FVSVNIJnBhc3N3b3JkPTEyMzQ1Njc4\nplatformID|4", peer);
    SendPacket(2, packet, peer);
	currentWorld = "";
}

void GrowtopiaBot::packet_type3(string text)
{
	dbgPrint("Some text is here: " + text);
	if (text.find("LOGON ATTEMPTS") != string::npos)
	{
		cout << "Wrong username / password!. (LOGON ATTEMPTS)";
	}
	if (text.find("password is wrong") != string::npos)
	{
		cout << "Wrong password!";
	}
	if (text.find("action|logon_fail") != string::npos)
	{
		connectClient();
		objects.clear();
		currentWorld = "";
	}
}

void GrowtopiaBot::packet_type6(string text)
{
	//dbgPrint("Some text is here: " + text);
	SendPacket(2, "action|enter_game\n", peer);
	enet_host_flush(client);
}

void GrowtopiaBot::packet_unknown(ENetPacket* packet)
{
	dbgPrint("Got unknown packet type: " + std::to_string(GetMessageTypeFromPacket(packet)));
	dbgPrint("Packet size is " + std::to_string(packet->dataLength));
}

void GrowtopiaBot::OnSendToServer(string address, int port, int userId, int token)
{
	login_user = userId;
	login_token = token;
	connectClient(address, port);
}

void GrowtopiaBot::OnConsoleMessage(string message) {
	cout << "Found console message: " << endl;
	string strippedMessage = stripMessage(message);
	cout << strippedMessage << endl;

	if (strippedMessage.find("MSG") != std::string::npos) {
		cout << "Found message!" << endl;
	}

	if (netID != owner) return;
	cout << strippedMessage << endl;
	if (strippedMessage.find("!pos") != string::npos)
	{
		for (ObjectData x : objects)
		{
			if (owner == x.netId)
			{
				SendPacket(2, "action|input\n|text|Owner pos is " + std::to_string(x.x) + ":" + std::to_string(x.y) + ".", peer);
			}
		}
	}
	if (strippedMessage.find("!follow") != string::npos)
	{
		isFollowing = true;
	}
	if (strippedMessage.find("!stop") != string::npos)
	{
		isFollowing = false;
	}
	if (strippedMessage.find("!dance") != string::npos)
	{
		SendPacket(2, "action|input\n|text|/dance", peer);
	}
	if (strippedMessage.find("!about") != string::npos || bubbleText.find("!help") != string::npos)
	{
	        SendPacket(2, "action|input\n|text|This is bot from Growtopia Noobs. Modified my DrOreo002", peer);
	

	cout << "------------------------" << endl;
}
}

void GrowtopiaBot::OnPlayPositioned(string sound)
{

}

void GrowtopiaBot::OnSetFreezeState(int state)
{

}

void GrowtopiaBot::OnRemove(string data) // "netID|x\n"
{
	std::stringstream ss(data.c_str());
	std::string to;
	int netID = -1;
	while (std::getline(ss, to, '\n')) {
		string id = to.substr(0, to.find("|"));
		string act = to.substr(to.find("|") + 1, to.length() - to.find("|"));
		if (id == "netID")
		{
			netID = atoi(act.c_str());
		}
		else {
			dbgPrint(id + "!!!!!!!!!!!" + act);
		}
	}
	for (ObjectData& objectData : objects)
	{
		if (objectData.netId == netID)
		{
			objectData.isGone = true;
		}
	}
	//SendPacket(2, "action|input\n|text|Bye bye ::((", peer);
}

void GrowtopiaBot::OnSpawn(string data)
{
	std::stringstream ss(data.c_str());
	std::string to;
	cout << data;
	ObjectData objectData;
	bool actuallyOwner = false;

	while (std::getline(ss, to, '\n')) {
		string id = to.substr(0, to.find("|"));
		string act = to.substr(to.find("|") + 1, to.length() - to.find("|") - 1);
		if (id == "country")
		{
			objectData.country = act;
		}
		else if (id == "name")
		{
			if (stripMessage(act) == ownerUsername) actuallyOwner = true;
			objectData.name = act;
		}
		else if (id == "netID")
		{
			if (actuallyOwner) owner = atoi(act.c_str());
			objectData.netId = atoi(act.c_str());
		}
		else if (id == "userID")
		{
			objectData.userId = atoi(act.c_str());
		}
		else if (id == "posXY")
		{
			int x = atoi(act.substr(0, to.find("|")).c_str());
			int y = atoi(act.substr(act.find("|") + 1, act.length() - act.find("|") - 1).c_str());
			objectData.x = x;
			objectData.y = y;
		}
		else if (id == "type")
		{
			if (act == "local")
				objectData.isLocal = true;
		}
		else if (act != "0" && (id == "invis" || id == "mstate" || id == "smstate"))
		{
			cout << "Some fishy boy is here: " << objectData.name << "; " << objectData.country << "; " << objectData.userId << "; " << objectData.netId << "; " << endl;
			objectData.isMod = true;
		}
	}

	if (actuallyOwner) cout << "Owner netID has been updated to " << objectData.netId << " username is " << ownerUsername;
	objects.push_back(objectData);
	//SendPacket(2, "action|input\n|text|`3Hello " + name + " `3with id " + netid + " from " + country + "! Your Growtopia ID is "+uid, peer);
}

void GrowtopiaBot::OnAction(string command)
{
	//SendPacket(2, "action|input\n|text|Why do you "+command.substr(1, command.length())+"?", peer);
}

void GrowtopiaBot::SetHasGrowID(int state, string name, string password)
{

}

void GrowtopiaBot::SetHasAccountSecured(int state)
{

}

void GrowtopiaBot::OnTalkBubble(int netID, string bubbleText, int type)
{
	if (netID != owner) return;
	cout << bubbleText << endl;
	if (bubbleText.find("!pos") != string::npos)
	{
		for (ObjectData x : objects)
		{
			if (owner == x.netId)
			{
				SendPacket(2, "action|input\n|text|Owner pos is " + std::to_string(x.x) + ":" + std::to_string(x.y) + ".", peer);
			}
		}
	}
	if (bubbleText.find("!follow") != string::npos)
	{
		isFollowing = true;
	}
	if (bubbleText.find("!stop") != string::npos)
	{
		isFollowing = false;
	}
	if (bubbleText.find("!dance") != string::npos)
	{
		SendPacket(2, "action|input\n|text|/dance", peer);
	}
	if (bubbleText.find("!about") != string::npos || bubbleText.find("!help") != string::npos)
	{
		SendPacket(2, "action|input\n|text|This is bot from Growtopia Noobs. Modified my DrOreo002", peer);
	}
}

void GrowtopiaBot::SetRespawnPos(int respawnPos)
{
	respawnX = respawnPos % 100; // hacky!!! TODO: get from world data (100)
	respawnY = respawnPos / 100; // hacky!!! TODO: get from world data (100)
}

void GrowtopiaBot::OnEmoticonDataChanged(int val1, string emoticons)
{

}

void GrowtopiaBot::OnSetPos(float x, float y)
{

}

void GrowtopiaBot::OnAddNotification(string image, string message, string audio, int val1) // You will see that when banned :(
{

}

/*

void GrowtopiaBot::OnFailedToEnterWorld()
{

}

void GrowtopiaBot::OnSuperMainStartAcceptLogonFB211131ddf(int val1, string domain, string folder, string deniedApps, string settings)
{

}

void GrowtopiaBot::OnSetBux(int val1, int val2, int val3) // missing params
{

}

void GrowtopiaBot::OnZoomCamera(float val1, int val2)
{

}

void GrowtopiaBot::OnGuildDataChanged(int val1, int val2, int val3, int val4)
{

}

void GrowtopiaBot::OnFactionDataChanged(int val1, int val2, int val3, string data)
{

}

void GrowtopiaBot::OnSetClothing(int hair, int shirt, int pants, int feet, int face, int hand, int back, int mask, int necklace, int val1, int val2, int val3, int val4)
{

}*/

void GrowtopiaBot::AtApplyTileDamage(int x, int y, int damge)
{
	cout << "Damage " + std::to_string(damge) + " applied at X:" + std::to_string(x) + " Y: " + std::to_string(y) << endl;
}

void GrowtopiaBot::AtApplyLock(int x, int y, int itemId) // ApplyLockFromGamePacket TODO: *(int*)(data + 4)
{
	SendPacket(2, "action|input\n|text|Lock " + std::to_string(itemId) + " applied at X:" + std::to_string(x) + " Y: " + std::to_string(y), peer);
}

void GrowtopiaBot::AtPlayerMoving(PlayerMoving* data)
{
	int object = -1;
	//cout << std::hex << data->characterState << "; " << data->x << "; " << data->y << "; "<< data->XSpeed << "; "<< data->plantingTree << endl;
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects.at(i).netId == data->netID)
		{
			object = i;
		}
	}
	if (object != -1)
	{
		objects[object].x = data->x;
		objects[object].y = data->y;
	}
	if (isFollowing && data->netID == owner && data->punchX == -1 && data->punchY == -1 && data->plantingTree == 0) // <--- bypass - can get banned from character state!!!, replacing isnt enought
	{
		if (backwardWalk)
			data->characterState ^= 0x10;
		if ((data->characterState & 0x800) && (data->characterState & 0x100)) {
			SendPacket(2, "action|respawn", peer);
		}
		for (int i = 0; i < objects.size(); i++)
			if (objects.at(i).isLocal) {
				objects.at(i).x = data->x;
				objects.at(i).y = data->y;
			}
		SendPacketRaw(4, packPlayerMoving(data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	}
}

void GrowtopiaBot::AtAvatarSetIconState(int netID, int state) // if player goes BRB, etc...
{

}

void GrowtopiaBot::WhenConnected()
{
	cout << "Connected to server!" << endl;
}

void GrowtopiaBot::WhenDisconnected()
{
	cout << "Disconnected from server..." << endl;
	connectClient();
}

int counter = 0; // 10ms per step

vector<string> explode(const string &delimiter, const string &str)
{
	vector<string> arr;

	int strleng = str.length();
	int delleng = delimiter.length();
	if (delleng == 0)
		return arr;//no change

	int i = 0;
	int k = 0;
	while (i < strleng)
	{
		int j = 0;
		while (i + j < strleng && j < delleng && str[i + j] == delimiter[j])
			j++;
		if (j == delleng)//found delimiter
		{
			arr.push_back(str.substr(k, i - k));
			i += delleng;
			k = i;
		}
		else
		{
			i++;
		}
	}
	arr.push_back(str.substr(k, i - k));
	return arr;
}

void GrowtopiaBot::userLoop() {
	if (timeFromWorldEnter > 200 && currentWorld != worldName) {
		if (worldName == "" || worldName == "-") {
			timeFromWorldEnter = 0;
		} else {
			SendPacket(3, "action|join_request\nname|" + worldName, peer); // MARRKS
			objects.clear();
		}
		timeFromWorldEnter = 0;
		currentWorld = worldName;
	}
	timeFromWorldEnter++;
	counter++;
	if ((counter % 1800) == 0)
	{
		string name = "";
		float distance = std::numeric_limits<float>::infinity();
		float ownerX;
		float ownerY;
		for (ObjectData x : objects)
		{
			if (x.netId == owner)
			{
				ownerX = x.x;
				ownerY = x.y;
			}
		}
	}
}

void GrowtopiaBot::userInit() {
	connectClient();
	cout << flush;
}

void GrowtopiaBot::respawn()
{
	PlayerMoving data;
	data.characterState = 0x924; // animation
	SendPacket(2, "action|respawn", peer); // respawn request
	for (int i = 0; i < objects.size(); i++)
		if (objects.at(i).isLocal)
		{
			data.x = objects.at(i).x;
			data.y = objects.at(i).y;
			data.netID = objects.at(i).netId;
			SendPacketRaw(4, packPlayerMoving(&data), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
			cout << "Send" << endl;
			break;
		}
}
