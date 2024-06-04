#include "pch.h"
#include "VTokenStream.h"

VTokenStream::VTokenStream() {

}

void VTokenStream::AddToken(VToken token) {

	m_Tokens.push_back(token);

}

VToken VTokenStream::GetNext() {

	auto token = m_Tokens[m_Index++];
	return token;

}

VToken VTokenStream::Peek(int delta) {

	return m_Tokens[m_Index + delta];

}

std::vector<VToken> VTokenStream::GetTokens() {

	return m_Tokens;

}

bool VTokenStream::End() {

	if (m_Index >= m_Tokens.size()) return true;
	return false;

}

void VTokenStream::Back() {

	m_Index--;

}